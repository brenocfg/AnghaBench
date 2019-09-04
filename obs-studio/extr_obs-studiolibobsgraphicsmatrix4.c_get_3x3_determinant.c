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

__attribute__((used)) static inline float get_3x3_determinant(const float *m)
{
	return (m[0] * ((m[4]*m[8]) - (m[7]*m[5]))) -
	       (m[1] * ((m[3]*m[8]) - (m[6]*m[5]))) +
	       (m[2] * ((m[3]*m[7]) - (m[6]*m[4])));
}