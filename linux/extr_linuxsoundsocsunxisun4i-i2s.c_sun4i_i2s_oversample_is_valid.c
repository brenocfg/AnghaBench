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
 int ARRAY_SIZE (unsigned int*) ; 
 unsigned int* sun4i_i2s_oversample_rates ; 

__attribute__((used)) static bool sun4i_i2s_oversample_is_valid(unsigned int oversample)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(sun4i_i2s_oversample_rates); i++)
		if (sun4i_i2s_oversample_rates[i] == oversample)
			return true;

	return false;
}