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
struct reset_controller_dev {int dummy; } ;
struct of_phandle_args {unsigned int* args; } ;

/* Variables and functions */
 unsigned int BERLIN_MAX_RESETS ; 
 int EINVAL ; 

__attribute__((used)) static int berlin_reset_xlate(struct reset_controller_dev *rcdev,
			      const struct of_phandle_args *reset_spec)
{
	unsigned offset, bit;

	offset = reset_spec->args[0];
	bit = reset_spec->args[1];

	if (bit >= BERLIN_MAX_RESETS)
		return -EINVAL;

	return (offset << 8) | bit;
}