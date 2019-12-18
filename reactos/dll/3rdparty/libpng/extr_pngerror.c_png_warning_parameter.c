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
typedef  int /*<<< orphan*/ * png_warning_parameters ;
typedef  int /*<<< orphan*/  png_const_charp ;

/* Variables and functions */
 int PNG_WARNING_PARAMETER_COUNT ; 
 int /*<<< orphan*/  png_safecat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
png_warning_parameter(png_warning_parameters p, int number,
    png_const_charp string)
{
   if (number > 0 && number <= PNG_WARNING_PARAMETER_COUNT)
      (void)png_safecat(p[number-1], (sizeof p[number-1]), 0, string);
}