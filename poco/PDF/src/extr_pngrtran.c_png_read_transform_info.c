#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structp ;
typedef  TYPE_2__* png_infop ;
typedef  scalar_t__ png_byte ;
struct TYPE_6__ {int color_type; int bit_depth; int channels; int /*<<< orphan*/  width; scalar_t__ pixel_depth; int /*<<< orphan*/  rowbytes; int /*<<< orphan*/  int_gamma; int /*<<< orphan*/  gamma; int /*<<< orphan*/  background; scalar_t__ num_trans; } ;
struct TYPE_5__ {int transformations; int flags; int user_transform_depth; int user_transform_channels; scalar_t__ palette_lookup; int /*<<< orphan*/  int_gamma; int /*<<< orphan*/  gamma; int /*<<< orphan*/  background; scalar_t__ num_trans; } ;

/* Variables and functions */
 int PNG_16_TO_8 ; 
 int PNG_ADD_ALPHA ; 
 int PNG_BACKGROUND ; 
 int PNG_COLOR_MASK_ALPHA ; 
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_COLOR_TYPE_GRAY ; 
 int PNG_COLOR_TYPE_PALETTE ; 
 int PNG_COLOR_TYPE_RGB ; 
 int PNG_COLOR_TYPE_RGB_ALPHA ; 
 int PNG_DITHER ; 
 int PNG_EXPAND ; 
 int PNG_EXPAND_tRNS ; 
 int PNG_FILLER ; 
 int PNG_FLAG_STRIP_ALPHA ; 
 int PNG_GAMMA ; 
 int PNG_GRAY_TO_RGB ; 
 int PNG_PACK ; 
 int PNG_RGB_TO_GRAY ; 
 int /*<<< orphan*/  PNG_ROWBYTES (scalar_t__,int /*<<< orphan*/ ) ; 
 int PNG_USER_TRANSFORM ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 

void /* PRIVATE */
png_read_transform_info(png_structp png_ptr, png_infop info_ptr)
{
   png_debug(1, "in png_read_transform_info\n");
#if defined(PNG_READ_EXPAND_SUPPORTED)
   if (png_ptr->transformations & PNG_EXPAND)
   {
      if (info_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
      {
         if (png_ptr->num_trans && (png_ptr->transformations & PNG_EXPAND_tRNS))
            info_ptr->color_type = PNG_COLOR_TYPE_RGB_ALPHA;
         else
            info_ptr->color_type = PNG_COLOR_TYPE_RGB;
         info_ptr->bit_depth = 8;
         info_ptr->num_trans = 0;
      }
      else
      {
         if (png_ptr->num_trans)
         {
            if (png_ptr->transformations & PNG_EXPAND_tRNS)
              info_ptr->color_type |= PNG_COLOR_MASK_ALPHA;
            else
              info_ptr->color_type |= PNG_COLOR_MASK_COLOR;
         }
         if (info_ptr->bit_depth < 8)
            info_ptr->bit_depth = 8;
         info_ptr->num_trans = 0;
      }
   }
#endif

#if defined(PNG_READ_BACKGROUND_SUPPORTED)
   if (png_ptr->transformations & PNG_BACKGROUND)
   {
      info_ptr->color_type &= ~PNG_COLOR_MASK_ALPHA;
      info_ptr->num_trans = 0;
      info_ptr->background = png_ptr->background;
   }
#endif

#if defined(PNG_READ_GAMMA_SUPPORTED)
   if (png_ptr->transformations & PNG_GAMMA)
   {
#ifdef PNG_FLOATING_POINT_SUPPORTED
      info_ptr->gamma = png_ptr->gamma;
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
      info_ptr->int_gamma = png_ptr->int_gamma;
#endif
   }
#endif

#if defined(PNG_READ_16_TO_8_SUPPORTED)
   if ((png_ptr->transformations & PNG_16_TO_8) && (info_ptr->bit_depth == 16))
      info_ptr->bit_depth = 8;
#endif

#if defined(PNG_READ_GRAY_TO_RGB_SUPPORTED)
   if (png_ptr->transformations & PNG_GRAY_TO_RGB)
      info_ptr->color_type |= PNG_COLOR_MASK_COLOR;
#endif

#if defined(PNG_READ_RGB_TO_GRAY_SUPPORTED)
   if (png_ptr->transformations & PNG_RGB_TO_GRAY)
      info_ptr->color_type &= ~PNG_COLOR_MASK_COLOR;
#endif

#if defined(PNG_READ_DITHER_SUPPORTED)
   if (png_ptr->transformations & PNG_DITHER)
   {
      if (((info_ptr->color_type == PNG_COLOR_TYPE_RGB) ||
         (info_ptr->color_type == PNG_COLOR_TYPE_RGB_ALPHA)) &&
         png_ptr->palette_lookup && info_ptr->bit_depth == 8)
      {
         info_ptr->color_type = PNG_COLOR_TYPE_PALETTE;
      }
   }
#endif

#if defined(PNG_READ_PACK_SUPPORTED)
   if ((png_ptr->transformations & PNG_PACK) && (info_ptr->bit_depth < 8))
      info_ptr->bit_depth = 8;
#endif

   if (info_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
      info_ptr->channels = 1;
   else if (info_ptr->color_type & PNG_COLOR_MASK_COLOR)
      info_ptr->channels = 3;
   else
      info_ptr->channels = 1;

#if defined(PNG_READ_STRIP_ALPHA_SUPPORTED)
   if (png_ptr->flags & PNG_FLAG_STRIP_ALPHA)
      info_ptr->color_type &= ~PNG_COLOR_MASK_ALPHA;
#endif

   if (info_ptr->color_type & PNG_COLOR_MASK_ALPHA)
      info_ptr->channels++;

#if defined(PNG_READ_FILLER_SUPPORTED)
   /* STRIP_ALPHA and FILLER allowed:  MASK_ALPHA bit stripped above */
   if ((png_ptr->transformations & PNG_FILLER) &&
       ((info_ptr->color_type == PNG_COLOR_TYPE_RGB) ||
       (info_ptr->color_type == PNG_COLOR_TYPE_GRAY)))
   {
      info_ptr->channels++;
      /* if adding a true alpha channel not just filler */
#if !defined(PNG_1_0_X)
      if (png_ptr->transformations & PNG_ADD_ALPHA)
        info_ptr->color_type |= PNG_COLOR_MASK_ALPHA;
#endif
   }
#endif

#if defined(PNG_USER_TRANSFORM_PTR_SUPPORTED) && \
defined(PNG_READ_USER_TRANSFORM_SUPPORTED)
   if(png_ptr->transformations & PNG_USER_TRANSFORM)
     {
       if(info_ptr->bit_depth < png_ptr->user_transform_depth)
         info_ptr->bit_depth = png_ptr->user_transform_depth;
       if(info_ptr->channels < png_ptr->user_transform_channels)
         info_ptr->channels = png_ptr->user_transform_channels;
     }
#endif

   info_ptr->pixel_depth = (png_byte)(info_ptr->channels *
      info_ptr->bit_depth);

   info_ptr->rowbytes = PNG_ROWBYTES(info_ptr->pixel_depth,info_ptr->width);

#if !defined(PNG_READ_EXPAND_SUPPORTED)
   if(png_ptr)
      return;
#endif
}