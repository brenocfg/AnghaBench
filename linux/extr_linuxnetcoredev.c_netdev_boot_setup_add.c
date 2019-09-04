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
struct netdev_boot_setup {char* name; int /*<<< orphan*/  map; } ;
struct ifmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int NETDEV_BOOT_SETUP_MAX ; 
 struct netdev_boot_setup* dev_boot_setup ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ifmap*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netdev_boot_setup_add(char *name, struct ifmap *map)
{
	struct netdev_boot_setup *s;
	int i;

	s = dev_boot_setup;
	for (i = 0; i < NETDEV_BOOT_SETUP_MAX; i++) {
		if (s[i].name[0] == '\0' || s[i].name[0] == ' ') {
			memset(s[i].name, 0, sizeof(s[i].name));
			strlcpy(s[i].name, name, IFNAMSIZ);
			memcpy(&s[i].map, map, sizeof(s[i].map));
			break;
		}
	}

	return i >= NETDEV_BOOT_SETUP_MAX ? 0 : 1;
}