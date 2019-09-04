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
 int EINVAL ; 
 int const SNC_VALIDATE_IN ; 

__attribute__((used)) static int boolean_validate(const int direction, const int value)
{
	if (direction == SNC_VALIDATE_IN) {
		if (value != 0 && value != 1)
			return -EINVAL;
	}
	return value;
}