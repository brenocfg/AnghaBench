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
typedef  scalar_t__ png_byte ;
struct TYPE_3__ {int bit_depth; scalar_t__ width; scalar_t__ channels; int rowbytes; scalar_t__ pixel_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_debug (int,char*) ; 

void /* PRIVATE */
png_do_chop(png_row_infop row_info, png_bytep row)
{
   png_debug(1, "in png_do_chop\n");
#if defined(PNG_USELESS_TESTS_SUPPORTED)
   if (row != NULL && row_info != NULL && row_info->bit_depth == 16)
#else
   if (row_info->bit_depth == 16)
#endif
   {
      png_bytep sp = row;
      png_bytep dp = row;
      png_uint_32 i;
      png_uint_32 istop = row_info->width * row_info->channels;

      for (i = 0; i<istop; i++, sp += 2, dp++)
      {
#if defined(PNG_READ_16_TO_8_ACCURATE_SCALE_SUPPORTED)
      /* This does a more accurate scaling of the 16-bit color
       * value, rather than a simple low-byte truncation.
       *
       * What the ideal calculation should be:
       *   *dp = (((((png_uint_32)(*sp) << 8) |
       *          (png_uint_32)(*(sp + 1))) * 255 + 127) / (png_uint_32)65535L;
       *
       * GRR: no, I think this is what it really should be:
       *   *dp = (((((png_uint_32)(*sp) << 8) |
       *           (png_uint_32)(*(sp + 1))) + 128L) / (png_uint_32)257L;
       *
       * GRR: here's the exact calculation with shifts:
       *   temp = (((png_uint_32)(*sp) << 8) | (png_uint_32)(*(sp + 1))) + 128L;
       *   *dp = (temp - (temp >> 8)) >> 8;
       *
       * Approximate calculation with shift/add instead of multiply/divide:
       *   *dp = ((((png_uint_32)(*sp) << 8) |
       *          (png_uint_32)((int)(*(sp + 1)) - *sp)) + 128) >> 8;
       *
       * What we actually do to avoid extra shifting and conversion:
       */

         *dp = *sp + ((((int)(*(sp + 1)) - *sp) > 128) ? 1 : 0);
#else
       /* Simply discard the low order byte */
         *dp = *sp;
#endif
      }
      row_info->bit_depth = 8;
      row_info->pixel_depth = (png_byte)(8 * row_info->channels);
      row_info->rowbytes = row_info->width * row_info->channels;
   }
}