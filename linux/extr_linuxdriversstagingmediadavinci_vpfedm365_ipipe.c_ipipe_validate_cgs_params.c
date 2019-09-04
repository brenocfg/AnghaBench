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
struct vpfe_ipipe_cgs {int en; scalar_t__ h_shft; } ;

/* Variables and functions */
 scalar_t__ CAR_SHIFT_MASK ; 
 int EINVAL ; 

__attribute__((used)) static int ipipe_validate_cgs_params(struct vpfe_ipipe_cgs *cgs)
{
	if (cgs->en > 1 || cgs->h_shft > CAR_SHIFT_MASK)
		return -EINVAL;

	return 0;
}