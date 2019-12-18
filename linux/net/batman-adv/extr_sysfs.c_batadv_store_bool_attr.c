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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int EINVAL ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  batadv_info (struct net_device*,char*,char const*,char*,...) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int batadv_store_bool_attr(char *buff, size_t count,
				  struct net_device *net_dev,
				  const char *attr_name, atomic_t *attr,
				  bool *changed)
{
	int enabled = -1;

	*changed = false;

	if (buff[count - 1] == '\n')
		buff[count - 1] = '\0';

	if ((strncmp(buff, "1", 2) == 0) ||
	    (strncmp(buff, "enable", 7) == 0) ||
	    (strncmp(buff, "enabled", 8) == 0))
		enabled = 1;

	if ((strncmp(buff, "0", 2) == 0) ||
	    (strncmp(buff, "disable", 8) == 0) ||
	    (strncmp(buff, "disabled", 9) == 0))
		enabled = 0;

	if (enabled < 0) {
		batadv_info(net_dev, "%s: Invalid parameter received: %s\n",
			    attr_name, buff);
		return -EINVAL;
	}

	if (atomic_read(attr) == enabled)
		return count;

	batadv_info(net_dev, "%s: Changing from: %s to: %s\n", attr_name,
		    atomic_read(attr) == 1 ? "enabled" : "disabled",
		    enabled == 1 ? "enabled" : "disabled");

	*changed = true;

	atomic_set(attr, (unsigned int)enabled);
	return count;
}