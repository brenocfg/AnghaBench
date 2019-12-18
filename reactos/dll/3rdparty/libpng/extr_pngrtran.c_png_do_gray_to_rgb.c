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
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_row_infop ;
typedef  void** png_bytep ;
typedef  void* png_byte ;
struct TYPE_3__ {scalar_t__ width; int bit_depth; int color_type; int channels; void* pixel_depth; int /*<<< orphan*/  rowbytes; } ;

/* Variables and functions */
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_COLOR_TYPE_GRAY ; 
 int PNG_COLOR_TYPE_GRAY_ALPHA ; 
 int /*<<< orphan*/  PNG_ROWBYTES (void*,scalar_t__) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 

__attribute__((used)) static void
png_do_gray_to_rgb(png_row_infop row_info, png_bytep row)
{
   png_uint_32 i;
   png_uint_32 row_width = row_info->width;

   png_debug(1, "in png_do_gray_to_rgb");

   if (row_info->bit_depth >= 8 &&
       (row_info->color_type & PNG_COLOR_MASK_COLOR) == 0)
   {
      if (row_info->color_type == PNG_COLOR_TYPE_GRAY)
      {
         if (row_info->bit_depth == 8)
         {
            /* This changes G to RGB */
            png_bytep sp = row + (size_t)row_width - 1;
            png_bytep dp = sp  + (size_t)row_width * 2;
            for (i = 0; i < row_width; i++)
            {
               *(dp--) = *sp;
               *(dp--) = *sp;
               *(dp--) = *(sp--);
            }
         }

         else
         {
            /* This changes GG to RRGGBB */
            png_bytep sp = row + (size_t)row_width * 2 - 1;
            png_bytep dp = sp  + (size_t)row_width * 4;
            for (i = 0; i < row_width; i++)
            {
               *(dp--) = *sp;
               *(dp--) = *(sp - 1);
               *(dp--) = *sp;
               *(dp--) = *(sp - 1);
               *(dp--) = *(sp--);
               *(dp--) = *(sp--);
            }
         }
      }

      else if (row_info->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
      {
         if (row_info->bit_depth == 8)
         {
            /* This changes GA to RGBA */
            png_bytep sp = row + (size_t)row_width * 2 - 1;
            png_bytep dp = sp  + (size_t)row_width * 2;
            for (i = 0; i < row_width; i++)
            {
               *(dp--) = *(sp--);
               *(dp--) = *sp;
               *(dp--) = *sp;
               *(dp--) = *(sp--);
            }
         }

         else
         {
            /* This changes GGAA to RRGGBBAA */
            png_bytep sp = row + (size_t)row_width * 4 - 1;
            png_bytep dp = sp  + (size_t)row_width * 4;
            for (i = 0; i < row_width; i++)
            {
               *(dp--) = *(sp--);
               *(dp--) = *(sp--);
               *(dp--) = *sp;
               *(dp--) = *(sp - 1);
               *(dp--) = *sp;
               *(dp--) = *(sp - 1);
               *(dp--) = *(sp--);
               *(dp--) = *(sp--);
            }
         }
      }
      row_info->channels = (png_byte)(row_info->channels + 2);
      row_info->color_type |= PNG_COLOR_MASK_COLOR;
      row_info->pixel_depth = (png_byte)(row_info->channels *
          row_info->bit_depth);
      row_info->rowbytes = PNG_ROWBYTES(row_info->pixel_depth, row_width);
   }
}