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
typedef  int png_uint_32 ;
typedef  int png_uint_16 ;
typedef  TYPE_1__* png_row_infop ;
typedef  TYPE_2__* png_color_8p ;
typedef  int* png_bytep ;
typedef  int png_byte ;
struct TYPE_6__ {int red; int green; int blue; int gray; int alpha; } ;
struct TYPE_5__ {int color_type; int width; int bit_depth; int rowbytes; } ;

/* Variables and functions */
 int PNG_COLOR_MASK_ALPHA ; 
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_COLOR_TYPE_PALETTE ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 

void /* PRIVATE */
png_do_unshift(png_row_infop row_info, png_bytep row, png_color_8p sig_bits)
{
   png_debug(1, "in png_do_unshift\n");
   if (
#if defined(PNG_USELESS_TESTS_SUPPORTED)
       row != NULL && row_info != NULL && sig_bits != NULL &&
#endif
       row_info->color_type != PNG_COLOR_TYPE_PALETTE)
   {
      int shift[4];
      int channels = 0;
      int c;
      png_uint_16 value = 0;
      png_uint_32 row_width = row_info->width;

      if (row_info->color_type & PNG_COLOR_MASK_COLOR)
      {
         shift[channels++] = row_info->bit_depth - sig_bits->red;
         shift[channels++] = row_info->bit_depth - sig_bits->green;
         shift[channels++] = row_info->bit_depth - sig_bits->blue;
      }
      else
      {
         shift[channels++] = row_info->bit_depth - sig_bits->gray;
      }
      if (row_info->color_type & PNG_COLOR_MASK_ALPHA)
      {
         shift[channels++] = row_info->bit_depth - sig_bits->alpha;
      }

      for (c = 0; c < channels; c++)
      {
         if (shift[c] <= 0)
            shift[c] = 0;
         else
            value = 1;
      }

      if (!value)
         return;

      switch (row_info->bit_depth)
      {
         case 2:
         {
            png_bytep bp;
            png_uint_32 i;
            png_uint_32 istop = row_info->rowbytes;

            for (bp = row, i = 0; i < istop; i++)
            {
               *bp >>= 1;
               *bp++ &= 0x55;
            }
            break;
         }
         case 4:
         {
            png_bytep bp = row;
            png_uint_32 i;
            png_uint_32 istop = row_info->rowbytes;
            png_byte mask = (png_byte)((((int)0xf0 >> shift[0]) & (int)0xf0) |
               (png_byte)((int)0xf >> shift[0]));

            for (i = 0; i < istop; i++)
            {
               *bp >>= shift[0];
               *bp++ &= mask;
            }
            break;
         }
         case 8:
         {
            png_bytep bp = row;
            png_uint_32 i;
            png_uint_32 istop = row_width * channels;

            for (i = 0; i < istop; i++)
            {
               *bp++ >>= shift[i%channels];
            }
            break;
         }
         case 16:
         {
            png_bytep bp = row;
            png_uint_32 i;
            png_uint_32 istop = channels * row_width;

            for (i = 0; i < istop; i++)
            {
               value = (png_uint_16)((*bp << 8) + *(bp + 1));
               value >>= shift[i%channels];
               *bp++ = (png_byte)(value >> 8);
               *bp++ = (png_byte)(value & 0xff);
            }
            break;
         }
      }
   }
}