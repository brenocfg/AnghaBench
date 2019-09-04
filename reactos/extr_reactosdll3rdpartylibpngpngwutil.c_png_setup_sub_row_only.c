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
typedef  scalar_t__* png_bytep ;
typedef  scalar_t__ png_byte ;
struct TYPE_3__ {scalar_t__* row_buf; scalar_t__* try_row; } ;

/* Variables and functions */
 scalar_t__ PNG_FILTER_VALUE_SUB ; 

__attribute__((used)) static void /* PRIVATE */
png_setup_sub_row_only(png_structrp png_ptr, png_uint_32 bpp,
    size_t row_bytes)
{
   png_bytep rp, dp, lp;
   size_t i;

   png_ptr->try_row[0] = PNG_FILTER_VALUE_SUB;

   for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1; i < bpp;
        i++, rp++, dp++)
   {
      *dp = *rp;
   }

   for (lp = png_ptr->row_buf + 1; i < row_bytes;
      i++, rp++, lp++, dp++)
   {
      *dp = (png_byte)(((int)*rp - (int)*lp) & 0xff);
   }
}