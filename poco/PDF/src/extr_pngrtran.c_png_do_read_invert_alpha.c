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
struct TYPE_3__ {scalar_t__ width; scalar_t__ color_type; int bit_depth; int rowbytes; } ;

/* Variables and functions */
 scalar_t__ PNG_COLOR_TYPE_GRAY_ALPHA ; 
 scalar_t__ PNG_COLOR_TYPE_RGB_ALPHA ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 

void /* PRIVATE */
png_do_read_invert_alpha(png_row_infop row_info, png_bytep row)
{
   png_debug(1, "in png_do_read_invert_alpha\n");
#if defined(PNG_USELESS_TESTS_SUPPORTED)
   if (row != NULL && row_info != NULL)
#endif
   {
      png_uint_32 row_width = row_info->width;
      if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
      {
         /* This inverts the alpha channel in RGBA */
         if (row_info->bit_depth == 8)
         {
            png_bytep sp = row + row_info->rowbytes;
            png_bytep dp = sp;
            png_uint_32 i;

            for (i = 0; i < row_width; i++)
            {
               *(--dp) = (png_byte)(255 - *(--sp));

/*             This does nothing:
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               We can replace it with:
*/
               sp-=3;
               dp=sp;
            }
         }
         /* This inverts the alpha channel in RRGGBBAA */
         else
         {
            png_bytep sp = row + row_info->rowbytes;
            png_bytep dp = sp;
            png_uint_32 i;

            for (i = 0; i < row_width; i++)
            {
               *(--dp) = (png_byte)(255 - *(--sp));
               *(--dp) = (png_byte)(255 - *(--sp));

/*             This does nothing:
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               We can replace it with:
*/
               sp-=6;
               dp=sp;
            }
         }
      }
      else if (row_info->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
      {
         /* This inverts the alpha channel in GA */
         if (row_info->bit_depth == 8)
         {
            png_bytep sp = row + row_info->rowbytes;
            png_bytep dp = sp;
            png_uint_32 i;

            for (i = 0; i < row_width; i++)
            {
               *(--dp) = (png_byte)(255 - *(--sp));
               *(--dp) = *(--sp);
            }
         }
         /* This inverts the alpha channel in GGAA */
         else
         {
            png_bytep sp  = row + row_info->rowbytes;
            png_bytep dp = sp;
            png_uint_32 i;

            for (i = 0; i < row_width; i++)
            {
               *(--dp) = (png_byte)(255 - *(--sp));
               *(--dp) = (png_byte)(255 - *(--sp));
/*
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
*/
               sp-=2;
               dp=sp;
            }
         }
      }
   }
}