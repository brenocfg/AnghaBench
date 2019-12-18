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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

double getTime(void)
{
  struct timeval tv;

  if (gettimeofday(&tv, NULL) < 0) return 0.0;
  else return (double)tv.tv_sec + ((double)tv.tv_usec / 1000000.);
}