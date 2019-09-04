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
 scalar_t__ GD_EPSILON ; 
 scalar_t__ fabs (double const) ; 

int gdAffineEqual (const double m1[6], const double m2[6])
{
  return (fabs (m1[0] - m2[0]) < GD_EPSILON &&
	  fabs (m1[1] - m2[1]) < GD_EPSILON &&
	  fabs (m1[2] - m2[2]) < GD_EPSILON &&
	  fabs (m1[3] - m2[3]) < GD_EPSILON &&
	  fabs (m1[4] - m2[4]) < GD_EPSILON &&
	  fabs (m1[5] - m2[5]) < GD_EPSILON);
}