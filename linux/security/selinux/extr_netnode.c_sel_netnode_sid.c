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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  sid; } ;
struct sel_netnode {TYPE_1__ nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sel_netnode* sel_netnode_find (void*,int /*<<< orphan*/ ) ; 
 int sel_netnode_sid_slow (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sel_netnode_sid(void *addr, u16 family, u32 *sid)
{
	struct sel_netnode *node;

	rcu_read_lock();
	node = sel_netnode_find(addr, family);
	if (node != NULL) {
		*sid = node->nsec.sid;
		rcu_read_unlock();
		return 0;
	}
	rcu_read_unlock();

	return sel_netnode_sid_slow(addr, family, sid);
}