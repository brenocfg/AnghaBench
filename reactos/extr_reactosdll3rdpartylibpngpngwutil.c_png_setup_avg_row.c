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
typedef  int /*<<< orphan*/ * png_bytep ;
typedef  void* png_byte ;
struct TYPE_3__ {int /*<<< orphan*/ * row_buf; int /*<<< orphan*/ * prev_row; int /*<<< orphan*/ * try_row; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_FILTER_VALUE_AVG ; 

__attribute__((used)) static size_t /* PRIVATE */
png_setup_avg_row(png_structrp png_ptr, png_uint_32 bpp,
    size_t row_bytes, size_t lmins)
{
   png_bytep rp, dp, pp, lp;
   png_uint_32 i;
   size_t sum = 0;
   unsigned int v;

   png_ptr->try_row[0] = PNG_FILTER_VALUE_AVG;

   for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1,
       pp = png_ptr->prev_row + 1; i < bpp; i++)
   {
      v = *dp++ = (png_byte)(((int)*rp++ - ((int)*pp++ / 2)) & 0xff);

#ifdef PNG_USE_ABS
      sum += 128 - abs((int)v - 128);
#else
      sum += (v < 128) ? v : 256 - v;
#endif
   }

   for (lp = png_ptr->row_buf + 1; i < row_bytes; i++)
   {
      v = *dp++ = (png_byte)(((int)*rp++ - (((int)*pp++ + (int)*lp++) / 2))
          & 0xff);

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