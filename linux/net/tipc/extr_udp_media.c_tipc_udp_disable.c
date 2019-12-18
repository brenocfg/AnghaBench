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
struct udp_bearer {int /*<<< orphan*/  work; int /*<<< orphan*/  bearer; TYPE_1__* ubsock; } ;
struct tipc_bearer {int /*<<< orphan*/  media_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  cleanup_bearer ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct udp_bearer* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_set_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tipc_udp_disable(struct tipc_bearer *b)
{
	struct udp_bearer *ub;

	ub = rtnl_dereference(b->media_ptr);
	if (!ub) {
		pr_err("UDP bearer instance not found\n");
		return;
	}
	sock_set_flag(ub->ubsock->sk, SOCK_DEAD);
	RCU_INIT_POINTER(ub->bearer, NULL);

	/* sock_release need to be done outside of rtnl lock */
	INIT_WORK(&ub->work, cleanup_bearer);
	schedule_work(&ub->work);
}