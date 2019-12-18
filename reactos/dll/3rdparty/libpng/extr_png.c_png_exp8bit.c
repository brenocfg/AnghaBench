#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_fixed_point ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int png_exp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static png_byte
png_exp8bit(png_fixed_point lg2)
{
   /* Get a 32-bit value: */
   png_uint_32 x = png_exp(lg2);

   /* Convert the 32-bit value to 0..255 by multiplying by 256-1. Note that the
    * second, rounding, step can't overflow because of the first, subtraction,
    * step.
    */
   x -= x >> 8;
   return (png_byte)(((x + 0x7fffffU) >> 24) & 0xff);
}