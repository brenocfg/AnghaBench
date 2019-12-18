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
typedef  int* png_bytep ;
typedef  int png_byte ;
struct TYPE_3__ {int color_type; scalar_t__ width; int bit_depth; } ;

/* Variables and functions */
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_COLOR_TYPE_RGB ; 
 int PNG_COLOR_TYPE_RGB_ALPHA ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 

__attribute__((used)) static void
png_do_read_intrapixel(png_row_infop row_info, png_bytep row)
{
   png_debug(1, "in png_do_read_intrapixel");

   if (
       (row_info->color_type & PNG_COLOR_MASK_COLOR) != 0)
   {
      int bytes_per_pixel;
      png_uint_32 row_width = row_info->width;

      if (row_info->bit_depth == 8)
      {
         png_bytep rp;
         png_uint_32 i;

         if (row_info->color_type == PNG_COLOR_TYPE_RGB)
            bytes_per_pixel = 3;

         else if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
            bytes_per_pixel = 4;

         else
            return;

         for (i = 0, rp = row; i < row_width; i++, rp += bytes_per_pixel)
         {
            *(rp) = (png_byte)((256 + *rp + *(rp + 1)) & 0xff);
            *(rp+2) = (png_byte)((256 + *(rp + 2) + *(rp + 1)) & 0xff);
         }
      }
      else if (row_info->bit_depth == 16)
      {
         png_bytep rp;
         png_uint_32 i;

         if (row_info->color_type == PNG_COLOR_TYPE_RGB)
            bytes_per_pixel = 6;

         else if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
            bytes_per_pixel = 8;

         else
            return;

         for (i = 0, rp = row; i < row_width; i++, rp += bytes_per_pixel)
         {
            png_uint_32 s0   = (png_uint_32)(*(rp    ) << 8) | *(rp + 1);
            png_uint_32 s1   = (png_uint_32)(*(rp + 2) << 8) | *(rp + 3);
            png_uint_32 s2   = (png_uint_32)(*(rp + 4) << 8) | *(rp + 5);
            png_uint_32 red  = (s0 + s1 + 65536) & 0xffff;
            png_uint_32 blue = (s2 + s1 + 65536) & 0xffff;
            *(rp    ) = (png_byte)((red >> 8) & 0xff);
            *(rp + 1) = (png_byte)(red & 0xff);
            *(rp + 4) = (png_byte)((blue >> 8) & 0xff);
            *(rp + 5) = (png_byte)(blue & 0xff);
         }
      }
   }
}