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
 int ARRAY_SIZE (unsigned char*) ; 
 int EINVAL ; 

__attribute__((used)) static int ad7606_oversampling_get_index(unsigned int val)
{
	unsigned char supported[] = {1, 2, 4, 8, 16, 32, 64};
	int i;

	for (i = 0; i < ARRAY_SIZE(supported); i++)
		if (val == supported[i])
			return i;

	return -EINVAL;
}