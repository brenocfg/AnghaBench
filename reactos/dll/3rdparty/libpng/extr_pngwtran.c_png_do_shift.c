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
typedef  unsigned int png_uint_32 ;
typedef  TYPE_1__* png_row_infop ;
typedef  TYPE_2__* png_const_color_8p ;
typedef  unsigned int* png_bytep ;
typedef  void* png_byte ;
struct TYPE_6__ {int red; int green; int blue; int gray; int alpha; } ;
struct TYPE_5__ {int color_type; int bit_depth; size_t rowbytes; unsigned int width; } ;

/* Variables and functions */
 int PNG_COLOR_MASK_ALPHA ; 
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_COLOR_TYPE_PALETTE ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 unsigned int png_get_uint_16 (unsigned int*) ; 

__attribute__((used)) static void
png_do_shift(png_row_infop row_info, png_bytep row,
    png_const_color_8p bit_depth)
{
   png_debug(1, "in png_do_shift");

   if (row_info->color_type != PNG_COLOR_TYPE_PALETTE)
   {
      int shift_start[4], shift_dec[4];
      unsigned int channels = 0;

      if ((row_info->color_type & PNG_COLOR_MASK_COLOR) != 0)
      {
         shift_start[channels] = row_info->bit_depth - bit_depth->red;
         shift_dec[channels] = bit_depth->red;
         channels++;

         shift_start[channels] = row_info->bit_depth - bit_depth->green;
         shift_dec[channels] = bit_depth->green;
         channels++;

         shift_start[channels] = row_info->bit_depth - bit_depth->blue;
         shift_dec[channels] = bit_depth->blue;
         channels++;
      }

      else
      {
         shift_start[channels] = row_info->bit_depth - bit_depth->gray;
         shift_dec[channels] = bit_depth->gray;
         channels++;
      }

      if ((row_info->color_type & PNG_COLOR_MASK_ALPHA) != 0)
      {
         shift_start[channels] = row_info->bit_depth - bit_depth->alpha;
         shift_dec[channels] = bit_depth->alpha;
         channels++;
      }

      /* With low row depths, could only be grayscale, so one channel */
      if (row_info->bit_depth < 8)
      {
         png_bytep bp = row;
         size_t i;
         unsigned int mask;
         size_t row_bytes = row_info->rowbytes;

         if (bit_depth->gray == 1 && row_info->bit_depth == 2)
            mask = 0x55;

         else if (row_info->bit_depth == 4 && bit_depth->gray == 3)
            mask = 0x11;

         else
            mask = 0xff;

         for (i = 0; i < row_bytes; i++, bp++)
         {
            int j;
            unsigned int v, out;

            v = *bp;
            out = 0;

            for (j = shift_start[0]; j > -shift_dec[0]; j -= shift_dec[0])
            {
               if (j > 0)
                  out |= v << j;

               else
                  out |= (v >> (-j)) & mask;
            }

            *bp = (png_byte)(out & 0xff);
         }
      }

      else if (row_info->bit_depth == 8)
      {
         png_bytep bp = row;
         png_uint_32 i;
         png_uint_32 istop = channels * row_info->width;

         for (i = 0; i < istop; i++, bp++)
         {
            unsigned int c = i%channels;
            int j;
            unsigned int v, out;

            v = *bp;
            out = 0;

            for (j = shift_start[c]; j > -shift_dec[c]; j -= shift_dec[c])
            {
               if (j > 0)
                  out |= v << j;

               else
                  out |= v >> (-j);
            }

            *bp = (png_byte)(out & 0xff);
         }
      }

      else
      {
         png_bytep bp;
         png_uint_32 i;
         png_uint_32 istop = channels * row_info->width;

         for (bp = row, i = 0; i < istop; i++)
         {
            unsigned int c = i%channels;
            int j;
            unsigned int value, v;

            v = png_get_uint_16(bp);
            value = 0;

            for (j = shift_start[c]; j > -shift_dec[c]; j -= shift_dec[c])
            {
               if (j > 0)
                  value |= v << j;

               else
                  value |= v >> (-j);
            }
            *bp++ = (png_byte)((value >> 8) & 0xff);
            *bp++ = (png_byte)(value & 0xff);
         }
      }
   }
}