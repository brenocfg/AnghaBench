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
 int DEG180 ; 
 unsigned char DEG270 ; 
 int DEG360 ; 
 int DEG90 ; 
 int HIGH_PEAK ; 
 int LOW_PEAK ; 
 int abs (int) ; 

__attribute__((used)) static unsigned int decode_erp(unsigned char a, unsigned char b)
{
	int weight_a, weight_b;
	int pos_a, pos_b;
	int ret;
	int range = HIGH_PEAK - LOW_PEAK;
	int mid_value = (HIGH_PEAK + LOW_PEAK) / 2;

	weight_b = abs(mid_value - a) - (range / 2 - 100) / 2;

	if (weight_b < 0)
		weight_b = 0;

	if (weight_b > 100)
		weight_b = 100;

	weight_a = 100 - weight_b;

	if (a < mid_value) {
		/* 0..90 and 270..360 degrees */
		pos_b = b - LOW_PEAK + DEG270;
		if (pos_b >= DEG360)
			pos_b -= DEG360;
	} else
		/* 90..270 degrees */
		pos_b = HIGH_PEAK - b + DEG90;


	if (b > mid_value)
		/* 0..180 degrees */
		pos_a = a - LOW_PEAK;
	else
		/* 180..360 degrees */
		pos_a = HIGH_PEAK - a + DEG180;

	/* interpolate both slider values, depending on weight factors */
	/* 0..99 x DEG360 */
	ret = pos_a * weight_a + pos_b * weight_b;

	/* normalize to 0..999 */
	ret *= 10;
	ret /= DEG360;

	if (ret < 0)
		ret += 1000;

	if (ret >= 1000)
		ret -= 1000;

	return ret;
}