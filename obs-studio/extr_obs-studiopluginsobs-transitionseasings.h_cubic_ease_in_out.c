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

__attribute__((used)) static inline float cubic_ease_in_out(float t)
{
	if (t < 0.5f) {
		return 4.0f * t * t * t;
	} else {
		float temp = (2.0f * t - 2.0f);
		return (t - 1.0f) * temp * temp + 1.0f;
	}
}