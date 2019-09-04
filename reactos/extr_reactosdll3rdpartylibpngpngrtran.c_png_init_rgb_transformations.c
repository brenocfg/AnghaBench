#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
struct TYPE_3__ {int color_type; scalar_t__ num_trans; int transformations; } ;

/* Variables and functions */
 int PNG_BACKGROUND_EXPAND ; 
 int PNG_COLOR_MASK_ALPHA ; 
 int PNG_COMPOSE ; 

__attribute__((used)) static void /* PRIVATE */
png_init_rgb_transformations(png_structrp png_ptr)
{
   /* Added to libpng-1.5.4: check the color type to determine whether there
    * is any alpha or transparency in the image and simply cancel the
    * background and alpha mode stuff if there isn't.
    */
   int input_has_alpha = (png_ptr->color_type & PNG_COLOR_MASK_ALPHA) != 0;
   int input_has_transparency = png_ptr->num_trans > 0;

   /* If no alpha we can optimize. */
   if (input_has_alpha == 0)
   {
      /* Any alpha means background and associative alpha processing is
       * required, however if the alpha is 0 or 1 throughout OPTIMIZE_ALPHA
       * and ENCODE_ALPHA are irrelevant.
       */
#     ifdef PNG_READ_ALPHA_MODE_SUPPORTED
         png_ptr->transformations &= ~PNG_ENCODE_ALPHA;
         png_ptr->flags &= ~PNG_FLAG_OPTIMIZE_ALPHA;
#     endif

      if (input_has_transparency == 0)
         png_ptr->transformations &= ~(PNG_COMPOSE | PNG_BACKGROUND_EXPAND);
   }

#if defined(PNG_READ_EXPAND_SUPPORTED) && defined(PNG_READ_BACKGROUND_SUPPORTED)
   /* png_set_background handling - deals with the complexity of whether the
    * background color is in the file format or the screen format in the case
    * where an 'expand' will happen.
    */

   /* The following code cannot be entered in the alpha pre-multiplication case
    * because PNG_BACKGROUND_EXPAND is cancelled below.
    */
   if ((png_ptr->transformations & PNG_BACKGROUND_EXPAND) != 0 &&
       (png_ptr->transformations & PNG_EXPAND) != 0 &&
       (png_ptr->color_type & PNG_COLOR_MASK_COLOR) == 0)
       /* i.e., GRAY or GRAY_ALPHA */
   {
      {
         /* Expand background and tRNS chunks */
         int gray = png_ptr->background.gray;
         int trans_gray = png_ptr->trans_color.gray;

         switch (png_ptr->bit_depth)
         {
            case 1:
               gray *= 0xff;
               trans_gray *= 0xff;
               break;

            case 2:
               gray *= 0x55;
               trans_gray *= 0x55;
               break;

            case 4:
               gray *= 0x11;
               trans_gray *= 0x11;
               break;

            default:

            case 8:
               /* FALLTHROUGH */ /*  (Already 8 bits) */

            case 16:
               /* Already a full 16 bits */
               break;
         }

         png_ptr->background.red = png_ptr->background.green =
            png_ptr->background.blue = (png_uint_16)gray;

         if ((png_ptr->transformations & PNG_EXPAND_tRNS) == 0)
         {
            png_ptr->trans_color.red = png_ptr->trans_color.green =
               png_ptr->trans_color.blue = (png_uint_16)trans_gray;
         }
      }
   } /* background expand and (therefore) no alpha association. */
#endif /* READ_EXPAND && READ_BACKGROUND */
}