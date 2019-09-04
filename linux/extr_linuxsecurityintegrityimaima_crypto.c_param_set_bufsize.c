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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_ORDER ; 
 int PAGE_SIZE ; 
 int get_order (unsigned long long) ; 
 int ima_bufsize ; 
 int ima_maxorder ; 
 unsigned long long memparse (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int param_set_bufsize(const char *val, const struct kernel_param *kp)
{
	unsigned long long size;
	int order;

	size = memparse(val, NULL);
	order = get_order(size);
	if (order >= MAX_ORDER)
		return -EINVAL;
	ima_maxorder = order;
	ima_bufsize = PAGE_SIZE << order;
	return 0;
}