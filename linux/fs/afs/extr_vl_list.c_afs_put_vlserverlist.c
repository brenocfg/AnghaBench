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
struct afs_vlserver_list {int nr_servers; TYPE_1__* servers; int /*<<< orphan*/  usage; } ;
struct afs_net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  server; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_put_vlserver (struct afs_net*,int /*<<< orphan*/ ) ; 
 unsigned int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct afs_vlserver_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

void afs_put_vlserverlist(struct afs_net *net, struct afs_vlserver_list *vllist)
{
	if (vllist) {
		unsigned int u = atomic_dec_return(&vllist->usage);

		//_debug("VLLS PUT %p{%u}", vllist, u);
		if (u == 0) {
			int i;

			for (i = 0; i < vllist->nr_servers; i++) {
				afs_put_vlserver(net, vllist->servers[i].server);
			}
			kfree_rcu(vllist, rcu);
		}
	}
}