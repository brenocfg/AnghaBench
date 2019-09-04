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
typedef  scalar_t__ uint ;
struct kernel_param {scalar_t__ arg; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WIL_RING_SIZE_ORDER_MAX ; 
 scalar_t__ WIL_RING_SIZE_ORDER_MIN ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int ring_order_set(const char *val, const struct kernel_param *kp)
{
	int ret;
	uint x;

	ret = kstrtouint(val, 0, &x);
	if (ret)
		return ret;

	if ((x < WIL_RING_SIZE_ORDER_MIN) || (x > WIL_RING_SIZE_ORDER_MAX))
		return -EINVAL;

	*((uint *)kp->arg) = x;

	return 0;
}