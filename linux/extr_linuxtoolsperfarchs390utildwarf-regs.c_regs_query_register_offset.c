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
 scalar_t__ errno ; 
 int /*<<< orphan*/  gprs ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 unsigned long strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  user_pt_regs ; 

int regs_query_register_offset(const char *name)
{
	unsigned long gpr;

	if (!name || strncmp(name, "%r", 2))
		return -EINVAL;

	errno = 0;
	gpr = strtoul(name + 2, NULL, 10);
	if (errno || gpr >= 16)
		return -EINVAL;

	return offsetof(user_pt_regs, gprs) + 8 * gpr;
}