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
struct datalink_proto {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct datalink_proto*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snap_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 

void unregister_snap_client(struct datalink_proto *proto)
{
	spin_lock_bh(&snap_lock);
	list_del_rcu(&proto->node);
	spin_unlock_bh(&snap_lock);

	synchronize_net();

	kfree(proto);
}