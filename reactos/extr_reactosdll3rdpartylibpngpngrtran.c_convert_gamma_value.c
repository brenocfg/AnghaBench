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
typedef  int /*<<< orphan*/  png_structrp ;
typedef  int /*<<< orphan*/  png_fixed_point ;

/* Variables and functions */
 double PNG_FP_1 ; 
 double PNG_FP_MAX ; 
 double PNG_FP_MIN ; 
 double floor (double) ; 
 int /*<<< orphan*/  png_fixed_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static png_fixed_point
convert_gamma_value(png_structrp png_ptr, double output_gamma)
{
   /* The following silently ignores cases where fixed point (times 100,000)
    * gamma values are passed to the floating point API.  This is safe and it
    * means the fixed point constants work just fine with the floating point
    * API.  The alternative would just lead to undetected errors and spurious
    * bug reports.  Negative values fail inside the _fixed API unless they
    * correspond to the flag values.
    */
   if (output_gamma > 0 && output_gamma < 128)
      output_gamma *= PNG_FP_1;

   /* This preserves -1 and -2 exactly: */
   output_gamma = floor(output_gamma + .5);

   if (output_gamma > PNG_FP_MAX || output_gamma < PNG_FP_MIN)
      png_fixed_error(png_ptr, "gamma value");

   return (png_fixed_point)output_gamma;
}