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
struct net_device {int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IFNAMSIZ ; 
 int __dev_alloc_name (struct net*,char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int dev_alloc_name_ns(struct net *net,
			     struct net_device *dev,
			     const char *name)
{
	char buf[IFNAMSIZ];
	int ret;

	BUG_ON(!net);
	ret = __dev_alloc_name(net, name, buf);
	if (ret >= 0)
		strlcpy(dev->name, buf, IFNAMSIZ);
	return ret;
}