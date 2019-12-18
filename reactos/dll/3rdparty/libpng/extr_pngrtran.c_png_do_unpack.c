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
typedef  int png_uint_32 ;
typedef  TYPE_1__* png_row_infop ;
typedef  int* png_bytep ;
typedef  void* png_byte ;
struct TYPE_3__ {int bit_depth; int width; int channels; int rowbytes; void* pixel_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_debug (int,char*) ; 

__attribute__((used)) static void
png_do_unpack(png_row_infop row_info, png_bytep row)
{
   png_debug(1, "in png_do_unpack");

   if (row_info->bit_depth < 8)
   {
      png_uint_32 i;
      png_uint_32 row_width=row_info->width;

      switch (row_info->bit_depth)
      {
         case 1:
         {
            png_bytep sp = row + (size_t)((row_width - 1) >> 3);
            png_bytep dp = row + (size_t)row_width - 1;
            png_uint_32 shift = 7U - ((row_width + 7U) & 0x07);
            for (i = 0; i < row_width; i++)
            {
               *dp = (png_byte)((*sp >> shift) & 0x01);

               if (shift == 7)
               {
                  shift = 0;
                  sp--;
               }

               else
                  shift++;

               dp--;
            }
            break;
         }

         case 2:
         {

            png_bytep sp = row + (size_t)((row_width - 1) >> 2);
            png_bytep dp = row + (size_t)row_width - 1;
            png_uint_32 shift = ((3U - ((row_width + 3U) & 0x03)) << 1);
            for (i = 0; i < row_width; i++)
            {
               *dp = (png_byte)((*sp >> shift) & 0x03);

               if (shift == 6)
               {
                  shift = 0;
                  sp--;
               }

               else
                  shift += 2;

               dp--;
            }
            break;
         }

         case 4:
         {
            png_bytep sp = row + (size_t)((row_width - 1) >> 1);
            png_bytep dp = row + (size_t)row_width - 1;
            png_uint_32 shift = ((1U - ((row_width + 1U) & 0x01)) << 2);
            for (i = 0; i < row_width; i++)
            {
               *dp = (png_byte)((*sp >> shift) & 0x0f);

               if (shift == 4)
               {
                  shift = 0;
                  sp--;
               }

               else
                  shift = 4;

               dp--;
            }
            break;
         }

         default:
            break;
      }
      row_info->bit_depth = 8;
      row_info->pixel_depth = (png_byte)(8 * row_info->channels);
      row_info->rowbytes = row_width * row_info->channels;
   }
}