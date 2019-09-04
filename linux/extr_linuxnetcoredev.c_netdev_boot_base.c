#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long base_addr; } ;
struct netdev_boot_setup {TYPE_1__ map; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int NETDEV_BOOT_SETUP_MAX ; 
 scalar_t__ __dev_get_by_name (int /*<<< orphan*/ *,char*) ; 
 struct netdev_boot_setup* dev_boot_setup ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,int) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

unsigned long netdev_boot_base(const char *prefix, int unit)
{
	const struct netdev_boot_setup *s = dev_boot_setup;
	char name[IFNAMSIZ];
	int i;

	sprintf(name, "%s%d", prefix, unit);

	/*
	 * If device already registered then return base of 1
	 * to indicate not to probe for this interface
	 */
	if (__dev_get_by_name(&init_net, name))
		return 1;

	for (i = 0; i < NETDEV_BOOT_SETUP_MAX; i++)
		if (!strcmp(name, s[i].name))
			return s[i].map.base_addr;
	return 0;
}