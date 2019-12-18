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
 scalar_t__ ceil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fabs (double) ; 
 int /*<<< orphan*/  log10 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

char *sigfig(double val, int figs, char *buf, int len)
{
  char format[80];
  int digitsAfterDecimal = figs - (int)ceil(log10(fabs(val)));

  if (digitsAfterDecimal < 1)
    snprintf(format, 80, "%%.0f");
  else
    snprintf(format, 80, "%%.%df", digitsAfterDecimal);
  snprintf(buf, len, format, val);
  return buf;
}