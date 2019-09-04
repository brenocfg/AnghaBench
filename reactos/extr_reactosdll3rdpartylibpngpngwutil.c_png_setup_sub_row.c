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
typedef  size_t png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  unsigned int* png_bytep ;
typedef  unsigned int png_byte ;
struct TYPE_3__ {unsigned int* try_row; unsigned int* row_buf; } ;

/* Variables and functions */
 unsigned int PNG_FILTER_VALUE_SUB ; 

__attribute__((used)) static size_t /* PRIVATE */
png_setup_sub_row(png_structrp png_ptr, png_uint_32 bpp,
    size_t row_bytes, size_t lmins)
{
   png_bytep rp, dp, lp;
   size_t i;
   size_t sum = 0;
   unsigned int v;

   png_ptr->try_row[0] = PNG_FILTER_VALUE_SUB;

   for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1; i < bpp;
        i++, rp++, dp++)
   {
      v = *dp = *rp;
#ifdef PNG_USE_ABS
      sum += 128 - abs((int)v - 128);
#else
      sum += (v < 128) ? v : 256 - v;
#endif
   }

   for (lp = png_ptr->row_buf + 1; i < row_bytes;
      i++, rp++, lp++, dp++)
   {
      v = *dp = (png_byte)(((int)*rp - (int)*lp) & 0xff);
#ifdef PNG_USE_ABS
      sum += 128 - abs((int)v - 128);
#else
      sum += (v < 128) ? v : 256 - v;
#endif

      if (sum > lmins)  /* We are already worse, don't continue. */
        break;
   }

   return (sum);
}