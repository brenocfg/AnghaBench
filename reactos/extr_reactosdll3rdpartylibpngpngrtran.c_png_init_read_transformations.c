#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
struct TYPE_5__ {scalar_t__ color_type; } ;

/* Variables and functions */
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_init_palette_transformations (TYPE_1__*) ; 
 int /*<<< orphan*/  png_init_rgb_transformations (TYPE_1__*) ; 

void /* PRIVATE */
png_init_read_transformations(png_structrp png_ptr)
{
   png_debug(1, "in png_init_read_transformations");

   /* This internal function is called from png_read_start_row in pngrutil.c
    * and it is called before the 'rowbytes' calculation is done, so the code
    * in here can change or update the transformations flags.
    *
    * First do updates that do not depend on the details of the PNG image data
    * being processed.
    */

#ifdef PNG_READ_GAMMA_SUPPORTED
   /* Prior to 1.5.4 these tests were performed from png_set_gamma, 1.5.4 adds
    * png_set_alpha_mode and this is another source for a default file gamma so
    * the test needs to be performed later - here.  In addition prior to 1.5.4
    * the tests were repeated for the PALETTE color type here - this is no
    * longer necessary (and doesn't seem to have been necessary before.)
    */
   {
      /* The following temporary indicates if overall gamma correction is
       * required.
       */
      int gamma_correction = 0;

      if (png_ptr->colorspace.gamma != 0) /* has been set */
      {
         if (png_ptr->screen_gamma != 0) /* screen set too */
            gamma_correction = png_gamma_threshold(png_ptr->colorspace.gamma,
                png_ptr->screen_gamma);

         else
            /* Assume the output matches the input; a long time default behavior
             * of libpng, although the standard has nothing to say about this.
             */
            png_ptr->screen_gamma = png_reciprocal(png_ptr->colorspace.gamma);
      }

      else if (png_ptr->screen_gamma != 0)
         /* The converse - assume the file matches the screen, note that this
          * perhaps undesirable default can (from 1.5.4) be changed by calling
          * png_set_alpha_mode (even if the alpha handling mode isn't required
          * or isn't changed from the default.)
          */
         png_ptr->colorspace.gamma = png_reciprocal(png_ptr->screen_gamma);

      else /* neither are set */
         /* Just in case the following prevents any processing - file and screen
          * are both assumed to be linear and there is no way to introduce a
          * third gamma value other than png_set_background with 'UNIQUE', and,
          * prior to 1.5.4
          */
         png_ptr->screen_gamma = png_ptr->colorspace.gamma = PNG_FP_1;

      /* We have a gamma value now. */
      png_ptr->colorspace.flags |= PNG_COLORSPACE_HAVE_GAMMA;

      /* Now turn the gamma transformation on or off as appropriate.  Notice
       * that PNG_GAMMA just refers to the file->screen correction.  Alpha
       * composition may independently cause gamma correction because it needs
       * linear data (e.g. if the file has a gAMA chunk but the screen gamma
       * hasn't been specified.)  In any case this flag may get turned off in
       * the code immediately below if the transform can be handled outside the
       * row loop.
       */
      if (gamma_correction != 0)
         png_ptr->transformations |= PNG_GAMMA;

      else
         png_ptr->transformations &= ~PNG_GAMMA;
   }
#endif

   /* Certain transformations have the effect of preventing other
    * transformations that happen afterward in png_do_read_transformations;
    * resolve the interdependencies here.  From the code of
    * png_do_read_transformations the order is:
    *
    *  1) PNG_EXPAND (including PNG_EXPAND_tRNS)
    *  2) PNG_STRIP_ALPHA (if no compose)
    *  3) PNG_RGB_TO_GRAY
    *  4) PNG_GRAY_TO_RGB iff !PNG_BACKGROUND_IS_GRAY
    *  5) PNG_COMPOSE
    *  6) PNG_GAMMA
    *  7) PNG_STRIP_ALPHA (if compose)
    *  8) PNG_ENCODE_ALPHA
    *  9) PNG_SCALE_16_TO_8
    * 10) PNG_16_TO_8
    * 11) PNG_QUANTIZE (converts to palette)
    * 12) PNG_EXPAND_16
    * 13) PNG_GRAY_TO_RGB iff PNG_BACKGROUND_IS_GRAY
    * 14) PNG_INVERT_MONO
    * 15) PNG_INVERT_ALPHA
    * 16) PNG_SHIFT
    * 17) PNG_PACK
    * 18) PNG_BGR
    * 19) PNG_PACKSWAP
    * 20) PNG_FILLER (includes PNG_ADD_ALPHA)
    * 21) PNG_SWAP_ALPHA
    * 22) PNG_SWAP_BYTES
    * 23) PNG_USER_TRANSFORM [must be last]
    */
#ifdef PNG_READ_STRIP_ALPHA_SUPPORTED
   if ((png_ptr->transformations & PNG_STRIP_ALPHA) != 0 &&
       (png_ptr->transformations & PNG_COMPOSE) == 0)
   {
      /* Stripping the alpha channel happens immediately after the 'expand'
       * transformations, before all other transformation, so it cancels out
       * the alpha handling.  It has the side effect negating the effect of
       * PNG_EXPAND_tRNS too:
       */
      png_ptr->transformations &= ~(PNG_BACKGROUND_EXPAND | PNG_ENCODE_ALPHA |
         PNG_EXPAND_tRNS);
      png_ptr->flags &= ~PNG_FLAG_OPTIMIZE_ALPHA;

      /* Kill the tRNS chunk itself too.  Prior to 1.5.4 this did not happen
       * so transparency information would remain just so long as it wasn't
       * expanded.  This produces unexpected API changes if the set of things
       * that do PNG_EXPAND_tRNS changes (perfectly possible given the
       * documentation - which says ask for what you want, accept what you
       * get.)  This makes the behavior consistent from 1.5.4:
       */
      png_ptr->num_trans = 0;
   }
#endif /* STRIP_ALPHA supported, no COMPOSE */

#ifdef PNG_READ_ALPHA_MODE_SUPPORTED
   /* If the screen gamma is about 1.0 then the OPTIMIZE_ALPHA and ENCODE_ALPHA
    * settings will have no effect.
    */
   if (png_gamma_significant(png_ptr->screen_gamma) == 0)
   {
      png_ptr->transformations &= ~PNG_ENCODE_ALPHA;
      png_ptr->flags &= ~PNG_FLAG_OPTIMIZE_ALPHA;
   }
#endif

#ifdef PNG_READ_RGB_TO_GRAY_SUPPORTED
   /* Make sure the coefficients for the rgb to gray conversion are set
    * appropriately.
    */
   if ((png_ptr->transformations & PNG_RGB_TO_GRAY) != 0)
      png_colorspace_set_rgb_coefficients(png_ptr);
#endif

#ifdef PNG_READ_GRAY_TO_RGB_SUPPORTED
#if defined(PNG_READ_EXPAND_SUPPORTED) && defined(PNG_READ_BACKGROUND_SUPPORTED)
   /* Detect gray background and attempt to enable optimization for
    * gray --> RGB case.
    *
    * Note:  if PNG_BACKGROUND_EXPAND is set and color_type is either RGB or
    * RGB_ALPHA (in which case need_expand is superfluous anyway), the
    * background color might actually be gray yet not be flagged as such.
    * This is not a problem for the current code, which uses
    * PNG_BACKGROUND_IS_GRAY only to decide when to do the
    * png_do_gray_to_rgb() transformation.
    *
    * TODO: this code needs to be revised to avoid the complexity and
    * interdependencies.  The color type of the background should be recorded in
    * png_set_background, along with the bit depth, then the code has a record
    * of exactly what color space the background is currently in.
    */
   if ((png_ptr->transformations & PNG_BACKGROUND_EXPAND) != 0)
   {
      /* PNG_BACKGROUND_EXPAND: the background is in the file color space, so if
       * the file was grayscale the background value is gray.
       */
      if ((png_ptr->color_type & PNG_COLOR_MASK_COLOR) == 0)
         png_ptr->mode |= PNG_BACKGROUND_IS_GRAY;
   }

   else if ((png_ptr->transformations & PNG_COMPOSE) != 0)
   {
      /* PNG_COMPOSE: png_set_background was called with need_expand false,
       * so the color is in the color space of the output or png_set_alpha_mode
       * was called and the color is black.  Ignore RGB_TO_GRAY because that
       * happens before GRAY_TO_RGB.
       */
      if ((png_ptr->transformations & PNG_GRAY_TO_RGB) != 0)
      {
         if (png_ptr->background.red == png_ptr->background.green &&
             png_ptr->background.red == png_ptr->background.blue)
         {
            png_ptr->mode |= PNG_BACKGROUND_IS_GRAY;
            png_ptr->background.gray = png_ptr->background.red;
         }
      }
   }
#endif /* READ_EXPAND && READ_BACKGROUND */
#endif /* READ_GRAY_TO_RGB */

   /* For indexed PNG data (PNG_COLOR_TYPE_PALETTE) many of the transformations
    * can be performed directly on the palette, and some (such as rgb to gray)
    * can be optimized inside the palette.  This is particularly true of the
    * composite (background and alpha) stuff, which can be pretty much all done
    * in the palette even if the result is expanded to RGB or gray afterward.
    *
    * NOTE: this is Not Yet Implemented, the code behaves as in 1.5.1 and
    * earlier and the palette stuff is actually handled on the first row.  This
    * leads to the reported bug that the palette returned by png_get_PLTE is not
    * updated.
    */
   if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
      png_init_palette_transformations(png_ptr);

   else
      png_init_rgb_transformations(png_ptr);

#if defined(PNG_READ_BACKGROUND_SUPPORTED) && \
   defined(PNG_READ_EXPAND_16_SUPPORTED)
   if ((png_ptr->transformations & PNG_EXPAND_16) != 0 &&
       (png_ptr->transformations & PNG_COMPOSE) != 0 &&
       (png_ptr->transformations & PNG_BACKGROUND_EXPAND) == 0 &&
       png_ptr->bit_depth != 16)
   {
      /* TODO: fix this.  Because the expand_16 operation is after the compose
       * handling the background color must be 8, not 16, bits deep, but the
       * application will supply a 16-bit value so reduce it here.
       *
       * The PNG_BACKGROUND_EXPAND code above does not expand to 16 bits at
       * present, so that case is ok (until do_expand_16 is moved.)
       *
       * NOTE: this discards the low 16 bits of the user supplied background
       * color, but until expand_16 works properly there is no choice!
       */
#     define CHOP(x) (x)=((png_uint_16)PNG_DIV257(x))
      CHOP(png_ptr->background.red);
      CHOP(png_ptr->background.green);
      CHOP(png_ptr->background.blue);
      CHOP(png_ptr->background.gray);
#     undef CHOP
   }
#endif /* READ_BACKGROUND && READ_EXPAND_16 */

#if defined(PNG_READ_BACKGROUND_SUPPORTED) && \
   (defined(PNG_READ_SCALE_16_TO_8_SUPPORTED) || \
   defined(PNG_READ_STRIP_16_TO_8_SUPPORTED))
   if ((png_ptr->transformations & (PNG_16_TO_8|PNG_SCALE_16_TO_8)) != 0 &&
       (png_ptr->transformations & PNG_COMPOSE) != 0 &&
       (png_ptr->transformations & PNG_BACKGROUND_EXPAND) == 0 &&
       png_ptr->bit_depth == 16)
   {
      /* On the other hand, if a 16-bit file is to be reduced to 8-bits per
       * component this will also happen after PNG_COMPOSE and so the background
       * color must be pre-expanded here.
       *
       * TODO: fix this too.
       */
      png_ptr->background.red = (png_uint_16)(png_ptr->background.red * 257);
      png_ptr->background.green =
         (png_uint_16)(png_ptr->background.green * 257);
      png_ptr->background.blue = (png_uint_16)(png_ptr->background.blue * 257);
      png_ptr->background.gray = (png_uint_16)(png_ptr->background.gray * 257);
   }
#endif

   /* NOTE: below 'PNG_READ_ALPHA_MODE_SUPPORTED' is presumed to also enable the
    * background support (see the comments in scripts/pnglibconf.dfa), this
    * allows pre-multiplication of the alpha channel to be implemented as
    * compositing on black.  This is probably sub-optimal and has been done in
    * 1.5.4 betas simply to enable external critique and testing (i.e. to
    * implement the new API quickly, without lots of internal changes.)
    */

#ifdef PNG_READ_GAMMA_SUPPORTED
#  ifdef PNG_READ_BACKGROUND_SUPPORTED
      /* Includes ALPHA_MODE */
      png_ptr->background_1 = png_ptr->background;
#  endif

   /* This needs to change - in the palette image case a whole set of tables are
    * built when it would be quicker to just calculate the correct value for
    * each palette entry directly.  Also, the test is too tricky - why check
    * PNG_RGB_TO_GRAY if PNG_GAMMA is not set?  The answer seems to be that
    * PNG_GAMMA is cancelled even if the gamma is known?  The test excludes the
    * PNG_COMPOSE case, so apparently if there is no *overall* gamma correction
    * the gamma tables will not be built even if composition is required on a
    * gamma encoded value.
    *
    * In 1.5.4 this is addressed below by an additional check on the individual
    * file gamma - if it is not 1.0 both RGB_TO_GRAY and COMPOSE need the
    * tables.
    */
   if ((png_ptr->transformations & PNG_GAMMA) != 0 ||
       ((png_ptr->transformations & PNG_RGB_TO_GRAY) != 0 &&
        (png_gamma_significant(png_ptr->colorspace.gamma) != 0 ||
         png_gamma_significant(png_ptr->screen_gamma) != 0)) ||
        ((png_ptr->transformations & PNG_COMPOSE) != 0 &&
         (png_gamma_significant(png_ptr->colorspace.gamma) != 0 ||
          png_gamma_significant(png_ptr->screen_gamma) != 0
#  ifdef PNG_READ_BACKGROUND_SUPPORTED
         || (png_ptr->background_gamma_type == PNG_BACKGROUND_GAMMA_UNIQUE &&
           png_gamma_significant(png_ptr->background_gamma) != 0)
#  endif
        )) || ((png_ptr->transformations & PNG_ENCODE_ALPHA) != 0 &&
       png_gamma_significant(png_ptr->screen_gamma) != 0))
   {
      png_build_gamma_table(png_ptr, png_ptr->bit_depth);

#ifdef PNG_READ_BACKGROUND_SUPPORTED
      if ((png_ptr->transformations & PNG_COMPOSE) != 0)
      {
         /* Issue a warning about this combination: because RGB_TO_GRAY is
          * optimized to do the gamma transform if present yet do_background has
          * to do the same thing if both options are set a
          * double-gamma-correction happens.  This is true in all versions of
          * libpng to date.
          */
         if ((png_ptr->transformations & PNG_RGB_TO_GRAY) != 0)
            png_warning(png_ptr,
                "libpng does not support gamma+background+rgb_to_gray");

         if ((png_ptr->color_type == PNG_COLOR_TYPE_PALETTE) != 0)
         {
            /* We don't get to here unless there is a tRNS chunk with non-opaque
             * entries - see the checking code at the start of this function.
             */
            png_color back, back_1;
            png_colorp palette = png_ptr->palette;
            int num_palette = png_ptr->num_palette;
            int i;
            if (png_ptr->background_gamma_type == PNG_BACKGROUND_GAMMA_FILE)
            {

               back.red = png_ptr->gamma_table[png_ptr->background.red];
               back.green = png_ptr->gamma_table[png_ptr->background.green];
               back.blue = png_ptr->gamma_table[png_ptr->background.blue];

               back_1.red = png_ptr->gamma_to_1[png_ptr->background.red];
               back_1.green = png_ptr->gamma_to_1[png_ptr->background.green];
               back_1.blue = png_ptr->gamma_to_1[png_ptr->background.blue];
            }
            else
            {
               png_fixed_point g, gs;

               switch (png_ptr->background_gamma_type)
               {
                  case PNG_BACKGROUND_GAMMA_SCREEN:
                     g = (png_ptr->screen_gamma);
                     gs = PNG_FP_1;
                     break;

                  case PNG_BACKGROUND_GAMMA_FILE:
                     g = png_reciprocal(png_ptr->colorspace.gamma);
                     gs = png_reciprocal2(png_ptr->colorspace.gamma,
                         png_ptr->screen_gamma);
                     break;

                  case PNG_BACKGROUND_GAMMA_UNIQUE:
                     g = png_reciprocal(png_ptr->background_gamma);
                     gs = png_reciprocal2(png_ptr->background_gamma,
                         png_ptr->screen_gamma);
                     break;
                  default:
                     g = PNG_FP_1;    /* back_1 */
                     gs = PNG_FP_1;   /* back */
                     break;
               }

               if (png_gamma_significant(gs) != 0)
               {
                  back.red = png_gamma_8bit_correct(png_ptr->background.red,
                      gs);
                  back.green = png_gamma_8bit_correct(png_ptr->background.green,
                      gs);
                  back.blue = png_gamma_8bit_correct(png_ptr->background.blue,
                      gs);
               }

               else
               {
                  back.red   = (png_byte)png_ptr->background.red;
                  back.green = (png_byte)png_ptr->background.green;
                  back.blue  = (png_byte)png_ptr->background.blue;
               }

               if (png_gamma_significant(g) != 0)
               {
                  back_1.red = png_gamma_8bit_correct(png_ptr->background.red,
                      g);
                  back_1.green = png_gamma_8bit_correct(
                      png_ptr->background.green, g);
                  back_1.blue = png_gamma_8bit_correct(png_ptr->background.blue,
                      g);
               }

               else
               {
                  back_1.red   = (png_byte)png_ptr->background.red;
                  back_1.green = (png_byte)png_ptr->background.green;
                  back_1.blue  = (png_byte)png_ptr->background.blue;
               }
            }

            for (i = 0; i < num_palette; i++)
            {
               if (i < (int)png_ptr->num_trans &&
                   png_ptr->trans_alpha[i] != 0xff)
               {
                  if (png_ptr->trans_alpha[i] == 0)
                  {
                     palette[i] = back;
                  }
                  else /* if (png_ptr->trans_alpha[i] != 0xff) */
                  {
                     png_byte v, w;

                     v = png_ptr->gamma_to_1[palette[i].red];
                     png_composite(w, v, png_ptr->trans_alpha[i], back_1.red);
                     palette[i].red = png_ptr->gamma_from_1[w];

                     v = png_ptr->gamma_to_1[palette[i].green];
                     png_composite(w, v, png_ptr->trans_alpha[i], back_1.green);
                     palette[i].green = png_ptr->gamma_from_1[w];

                     v = png_ptr->gamma_to_1[palette[i].blue];
                     png_composite(w, v, png_ptr->trans_alpha[i], back_1.blue);
                     palette[i].blue = png_ptr->gamma_from_1[w];
                  }
               }
               else
               {
                  palette[i].red = png_ptr->gamma_table[palette[i].red];
                  palette[i].green = png_ptr->gamma_table[palette[i].green];
                  palette[i].blue = png_ptr->gamma_table[palette[i].blue];
               }
            }

            /* Prevent the transformations being done again.
             *
             * NOTE: this is highly dubious; it removes the transformations in
             * place.  This seems inconsistent with the general treatment of the
             * transformations elsewhere.
             */
            png_ptr->transformations &= ~(PNG_COMPOSE | PNG_GAMMA);
         } /* color_type == PNG_COLOR_TYPE_PALETTE */

         /* if (png_ptr->background_gamma_type!=PNG_BACKGROUND_GAMMA_UNKNOWN) */
         else /* color_type != PNG_COLOR_TYPE_PALETTE */
         {
            int gs_sig, g_sig;
            png_fixed_point g = PNG_FP_1;  /* Correction to linear */
            png_fixed_point gs = PNG_FP_1; /* Correction to screen */

            switch (png_ptr->background_gamma_type)
            {
               case PNG_BACKGROUND_GAMMA_SCREEN:
                  g = png_ptr->screen_gamma;
                  /* gs = PNG_FP_1; */
                  break;

               case PNG_BACKGROUND_GAMMA_FILE:
                  g = png_reciprocal(png_ptr->colorspace.gamma);
                  gs = png_reciprocal2(png_ptr->colorspace.gamma,
                      png_ptr->screen_gamma);
                  break;

               case PNG_BACKGROUND_GAMMA_UNIQUE:
                  g = png_reciprocal(png_ptr->background_gamma);
                  gs = png_reciprocal2(png_ptr->background_gamma,
                      png_ptr->screen_gamma);
                  break;

               default:
                  png_error(png_ptr, "invalid background gamma type");
            }

            g_sig = png_gamma_significant(g);
            gs_sig = png_gamma_significant(gs);

            if (g_sig != 0)
               png_ptr->background_1.gray = png_gamma_correct(png_ptr,
                   png_ptr->background.gray, g);

            if (gs_sig != 0)
               png_ptr->background.gray = png_gamma_correct(png_ptr,
                   png_ptr->background.gray, gs);

            if ((png_ptr->background.red != png_ptr->background.green) ||
                (png_ptr->background.red != png_ptr->background.blue) ||
                (png_ptr->background.red != png_ptr->background.gray))
            {
               /* RGB or RGBA with color background */
               if (g_sig != 0)
               {
                  png_ptr->background_1.red = png_gamma_correct(png_ptr,
                      png_ptr->background.red, g);

                  png_ptr->background_1.green = png_gamma_correct(png_ptr,
                      png_ptr->background.green, g);

                  png_ptr->background_1.blue = png_gamma_correct(png_ptr,
                      png_ptr->background.blue, g);
               }

               if (gs_sig != 0)
               {
                  png_ptr->background.red = png_gamma_correct(png_ptr,
                      png_ptr->background.red, gs);

                  png_ptr->background.green = png_gamma_correct(png_ptr,
                      png_ptr->background.green, gs);

                  png_ptr->background.blue = png_gamma_correct(png_ptr,
                      png_ptr->background.blue, gs);
               }
            }

            else
            {
               /* GRAY, GRAY ALPHA, RGB, or RGBA with gray background */
               png_ptr->background_1.red = png_ptr->background_1.green
                   = png_ptr->background_1.blue = png_ptr->background_1.gray;

               png_ptr->background.red = png_ptr->background.green
                   = png_ptr->background.blue = png_ptr->background.gray;
            }

            /* The background is now in screen gamma: */
            png_ptr->background_gamma_type = PNG_BACKGROUND_GAMMA_SCREEN;
         } /* color_type != PNG_COLOR_TYPE_PALETTE */
      }/* png_ptr->transformations & PNG_BACKGROUND */

      else
      /* Transformation does not include PNG_BACKGROUND */
#endif /* READ_BACKGROUND */
      if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE
#ifdef PNG_READ_RGB_TO_GRAY_SUPPORTED
         /* RGB_TO_GRAY needs to have non-gamma-corrected values! */
         && ((png_ptr->transformations & PNG_EXPAND) == 0 ||
         (png_ptr->transformations & PNG_RGB_TO_GRAY) == 0)
#endif
         )
      {
         png_colorp palette = png_ptr->palette;
         int num_palette = png_ptr->num_palette;
         int i;

         /* NOTE: there are other transformations that should probably be in
          * here too.
          */
         for (i = 0; i < num_palette; i++)
         {
            palette[i].red = png_ptr->gamma_table[palette[i].red];
            palette[i].green = png_ptr->gamma_table[palette[i].green];
            palette[i].blue = png_ptr->gamma_table[palette[i].blue];
         }

         /* Done the gamma correction. */
         png_ptr->transformations &= ~PNG_GAMMA;
      } /* color_type == PALETTE && !PNG_BACKGROUND transformation */
   }
#ifdef PNG_READ_BACKGROUND_SUPPORTED
   else
#endif
#endif /* READ_GAMMA */

#ifdef PNG_READ_BACKGROUND_SUPPORTED
   /* No GAMMA transformation (see the hanging else 4 lines above) */
   if ((png_ptr->transformations & PNG_COMPOSE) != 0 &&
       (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE))
   {
      int i;
      int istop = (int)png_ptr->num_trans;
      png_color back;
      png_colorp palette = png_ptr->palette;

      back.red   = (png_byte)png_ptr->background.red;
      back.green = (png_byte)png_ptr->background.green;
      back.blue  = (png_byte)png_ptr->background.blue;

      for (i = 0; i < istop; i++)
      {
         if (png_ptr->trans_alpha[i] == 0)
         {
            palette[i] = back;
         }

         else if (png_ptr->trans_alpha[i] != 0xff)
         {
            /* The png_composite() macro is defined in png.h */
            png_composite(palette[i].red, palette[i].red,
                png_ptr->trans_alpha[i], back.red);

            png_composite(palette[i].green, palette[i].green,
                png_ptr->trans_alpha[i], back.green);

            png_composite(palette[i].blue, palette[i].blue,
                png_ptr->trans_alpha[i], back.blue);
         }
      }

      png_ptr->transformations &= ~PNG_COMPOSE;
   }
#endif /* READ_BACKGROUND */

#ifdef PNG_READ_SHIFT_SUPPORTED
   if ((png_ptr->transformations & PNG_SHIFT) != 0 &&
       (png_ptr->transformations & PNG_EXPAND) == 0 &&
       (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE))
   {
      int i;
      int istop = png_ptr->num_palette;
      int shift = 8 - png_ptr->sig_bit.red;

      png_ptr->transformations &= ~PNG_SHIFT;

      /* significant bits can be in the range 1 to 7 for a meaningful result, if
       * the number of significant bits is 0 then no shift is done (this is an
       * error condition which is silently ignored.)
       */
      if (shift > 0 && shift < 8)
         for (i=0; i<istop; ++i)
         {
            int component = png_ptr->palette[i].red;

            component >>= shift;
            png_ptr->palette[i].red = (png_byte)component;
         }

      shift = 8 - png_ptr->sig_bit.green;
      if (shift > 0 && shift < 8)
         for (i=0; i<istop; ++i)
         {
            int component = png_ptr->palette[i].green;

            component >>= shift;
            png_ptr->palette[i].green = (png_byte)component;
         }

      shift = 8 - png_ptr->sig_bit.blue;
      if (shift > 0 && shift < 8)
         for (i=0; i<istop; ++i)
         {
            int component = png_ptr->palette[i].blue;

            component >>= shift;
            png_ptr->palette[i].blue = (png_byte)component;
         }
   }
#endif /* READ_SHIFT */
}