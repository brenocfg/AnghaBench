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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  sid; } ;
struct sel_netport {TYPE_1__ psec; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sel_netport* sel_netport_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sel_netport_sid_slow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sel_netport_sid(u8 protocol, u16 pnum, u32 *sid)
{
	struct sel_netport *port;

	rcu_read_lock();
	port = sel_netport_find(protocol, pnum);
	if (port != NULL) {
		*sid = port->psec.sid;
		rcu_read_unlock();
		return 0;
	}
	rcu_read_unlock();

	return sel_netport_sid_slow(protocol, pnum, sid);
}