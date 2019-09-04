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
 int GD_TRUE ; 

int gdAffineConcat (double dst[6], const double m1[6], const double m2[6])
{
	double dst0, dst1, dst2, dst3, dst4, dst5;

	dst0 = m1[0] * m2[0] + m1[1] * m2[2];
	dst1 = m1[0] * m2[1] + m1[1] * m2[3];
	dst2 = m1[2] * m2[0] + m1[3] * m2[2];
	dst3 = m1[2] * m2[1] + m1[3] * m2[3];
	dst4 = m1[4] * m2[0] + m1[5] * m2[2] + m2[4];
	dst5 = m1[4] * m2[1] + m1[5] * m2[3] + m2[5];
	dst[0] = dst0;
	dst[1] = dst1;
	dst[2] = dst2;
	dst[3] = dst3;
	dst[4] = dst4;
	dst[5] = dst5;
	return GD_TRUE;
}