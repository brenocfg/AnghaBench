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

/* Variables and functions */
 int DBL_MIN_10_EXP ; 

__attribute__((used)) static double
png_pow10(int power)
{
   int recip = 0;
   double d = 1;

   /* Handle negative exponent with a reciprocal at the end because
    * 10 is exact whereas .1 is inexact in base 2
    */
   if (power < 0)
   {
      if (power < DBL_MIN_10_EXP) return 0;
      recip = 1; power = -power;
   }

   if (power > 0)
   {
      /* Decompose power bitwise. */
      double mult = 10;
      do
      {
         if (power & 1) d *= mult;
         mult *= mult;
         power >>= 1;
      }
      while (power > 0);

      if (recip != 0) d = 1/d;
   }
   /* else power is 0 and d is 1 */

   return d;
}