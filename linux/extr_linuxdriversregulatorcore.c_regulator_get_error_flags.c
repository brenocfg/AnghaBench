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
struct regulator {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int _regulator_get_error_flags (int /*<<< orphan*/ ,unsigned int*) ; 

int regulator_get_error_flags(struct regulator *regulator,
				unsigned int *flags)
{
	return _regulator_get_error_flags(regulator->rdev, flags);
}