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
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  xen_initial_domain () ; 
 int xenbus_scanf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

__attribute__((used)) static int vcpu_online(unsigned int cpu)
{
	int err;
	char dir[16], state[16];

	sprintf(dir, "cpu/%u", cpu);
	err = xenbus_scanf(XBT_NIL, dir, "availability", "%15s", state);
	if (err != 1) {
		if (!xen_initial_domain())
			pr_err("Unable to read cpu state\n");
		return err;
	}

	if (strcmp(state, "online") == 0)
		return 1;
	else if (strcmp(state, "offline") == 0)
		return 0;

	pr_err("unknown state(%s) on CPU%d\n", state, cpu);
	return -EINVAL;
}