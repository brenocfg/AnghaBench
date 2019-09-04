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
 scalar_t__ XEN_BUS_ID_SIZE ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int frontend_bus_id(char bus_id[XEN_BUS_ID_SIZE], const char *nodename)
{
	nodename = strchr(nodename, '/');
	if (!nodename || strlen(nodename + 1) >= XEN_BUS_ID_SIZE) {
		pr_warn("bad frontend %s\n", nodename);
		return -EINVAL;
	}

	strlcpy(bus_id, nodename + 1, XEN_BUS_ID_SIZE);
	if (!strchr(bus_id, '/')) {
		pr_warn("bus_id %s no slash\n", bus_id);
		return -EINVAL;
	}
	*strchr(bus_id, '/') = '-';
	return 0;
}