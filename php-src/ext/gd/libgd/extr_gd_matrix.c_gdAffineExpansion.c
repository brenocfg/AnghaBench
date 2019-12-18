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
 int /*<<< orphan*/  fabs (double const) ; 
 double sqrt (int /*<<< orphan*/ ) ; 

double gdAffineExpansion (const double src[6])
{
  return sqrt (fabs (src[0] * src[3] - src[1] * src[2]));
}