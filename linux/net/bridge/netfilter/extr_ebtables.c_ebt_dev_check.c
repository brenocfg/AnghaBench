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
struct net_device {char* name; } ;

/* Variables and functions */

__attribute__((used)) static inline int
ebt_dev_check(const char *entry, const struct net_device *device)
{
	int i = 0;
	const char *devname;

	if (*entry == '\0')
		return 0;
	if (!device)
		return 1;
	devname = device->name;
	/* 1 is the wildcard token */
	while (entry[i] != '\0' && entry[i] != 1 && entry[i] == devname[i])
		i++;
	return devname[i] != entry[i] && entry[i] != 1;
}