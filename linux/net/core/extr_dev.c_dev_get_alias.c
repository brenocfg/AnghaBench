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
struct net_device {int /*<<< orphan*/  ifalias; } ;
struct dev_ifalias {char* ifalias; } ;

/* Variables and functions */
 struct dev_ifalias* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int snprintf (char*,size_t,char*,char*) ; 

int dev_get_alias(const struct net_device *dev, char *name, size_t len)
{
	const struct dev_ifalias *alias;
	int ret = 0;

	rcu_read_lock();
	alias = rcu_dereference(dev->ifalias);
	if (alias)
		ret = snprintf(name, len, "%s", alias->ifalias);
	rcu_read_unlock();

	return ret;
}