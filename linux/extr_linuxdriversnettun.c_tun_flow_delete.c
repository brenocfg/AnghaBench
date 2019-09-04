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
struct tun_struct {int /*<<< orphan*/  flow_count; } ;
struct tun_flow_entry {int /*<<< orphan*/  hash_link; int /*<<< orphan*/  queue_index; int /*<<< orphan*/  rxhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct tun_flow_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  tun_debug (int /*<<< orphan*/ ,struct tun_struct*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tun_flow_delete(struct tun_struct *tun, struct tun_flow_entry *e)
{
	tun_debug(KERN_INFO, tun, "delete flow: hash %u index %u\n",
		  e->rxhash, e->queue_index);
	hlist_del_rcu(&e->hash_link);
	kfree_rcu(e, rcu);
	--tun->flow_count;
}