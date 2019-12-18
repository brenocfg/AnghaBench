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
struct afs_vlserver {int /*<<< orphan*/  rcu; int /*<<< orphan*/  usage; } ;
struct afs_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_vlserver_rcu ; 
 unsigned int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void afs_put_vlserver(struct afs_net *net, struct afs_vlserver *vlserver)
{
	if (vlserver) {
		unsigned int u = atomic_dec_return(&vlserver->usage);
		//_debug("VL PUT %p{%u}", vlserver, u);

		if (u == 0)
			call_rcu(&vlserver->rcu, afs_vlserver_rcu);
	}
}