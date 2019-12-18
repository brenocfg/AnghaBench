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

void nvgTransformPoint(float* dx, float* dy, const float* t, float sx, float sy)
{
	*dx = sx*t[0] + sy*t[2] + t[4];
	*dy = sx*t[1] + sy*t[3] + t[5];
}