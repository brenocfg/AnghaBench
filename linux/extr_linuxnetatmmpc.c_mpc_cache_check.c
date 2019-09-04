#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_5__ {unsigned long mpc_p4; unsigned long mpc_p5; } ;
struct mpoa_client {struct mpoa_client* next; TYPE_3__* in_ops; TYPE_2__ parameters; TYPE_1__* eg_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* refresh ) (struct mpoa_client*) ;int /*<<< orphan*/  (* check_resolving ) (struct mpoa_client*) ;int /*<<< orphan*/  (* clear_count ) (struct mpoa_client*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* clear_expired ) (struct mpoa_client*) ;} ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long checking_time ; 
 int /*<<< orphan*/  mpc_timer_refresh () ; 
 struct mpoa_client* mpcs ; 
 int /*<<< orphan*/  stub1 (struct mpoa_client*) ; 
 int /*<<< orphan*/  stub2 (struct mpoa_client*) ; 
 int /*<<< orphan*/  stub3 (struct mpoa_client*) ; 
 int /*<<< orphan*/  stub4 (struct mpoa_client*) ; 

__attribute__((used)) static void mpc_cache_check(struct timer_list *unused)
{
	struct mpoa_client *mpc = mpcs;
	static unsigned long previous_resolving_check_time;
	static unsigned long previous_refresh_time;

	while (mpc != NULL) {
		mpc->in_ops->clear_count(mpc);
		mpc->eg_ops->clear_expired(mpc);
		if (checking_time - previous_resolving_check_time >
		    mpc->parameters.mpc_p4 * HZ) {
			mpc->in_ops->check_resolving(mpc);
			previous_resolving_check_time = checking_time;
		}
		if (checking_time - previous_refresh_time >
		    mpc->parameters.mpc_p5 * HZ) {
			mpc->in_ops->refresh(mpc);
			previous_refresh_time = checking_time;
		}
		mpc = mpc->next;
	}
	mpc_timer_refresh();
}