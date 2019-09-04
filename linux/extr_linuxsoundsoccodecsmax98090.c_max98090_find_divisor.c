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
 int ARRAY_SIZE (int*) ; 
 int INT_MAX ; 
 int abs (int) ; 
 int* dmic_divisors ; 

__attribute__((used)) static int max98090_find_divisor(int target_freq, int pclk)
{
	int current_diff = INT_MAX;
	int test_diff = INT_MAX;
	int divisor_index = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(dmic_divisors); i++) {
		test_diff = abs(target_freq - (pclk / dmic_divisors[i]));
		if (test_diff < current_diff) {
			current_diff = test_diff;
			divisor_index = i;
		}
	}

	return divisor_index;
}