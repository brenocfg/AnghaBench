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
struct net_bridge_port {TYPE_1__* dev; int /*<<< orphan*/  backup_port; } ;
typedef  int ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 struct net_bridge_port* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t show_backup_port(struct net_bridge_port *p, char *buf)
{
	struct net_bridge_port *backup_p;
	int ret = 0;

	rcu_read_lock();
	backup_p = rcu_dereference(p->backup_port);
	if (backup_p)
		ret = sprintf(buf, "%s\n", backup_p->dev->name);
	rcu_read_unlock();

	return ret;
}