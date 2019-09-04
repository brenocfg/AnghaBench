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
struct TYPE_2__ {int /*<<< orphan*/  mpc_p6; int /*<<< orphan*/  mpc_p5; int /*<<< orphan*/  mpc_p4; int /*<<< orphan*/  mpc_p3; int /*<<< orphan*/  mpc_p2; int /*<<< orphan*/  mpc_p1; } ;
struct mpoa_client {TYPE_1__ parameters; struct mpoa_client* next; int /*<<< orphan*/  egress_lock; int /*<<< orphan*/  ingress_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MPC_P1 ; 
 int /*<<< orphan*/  MPC_P2 ; 
 int /*<<< orphan*/  MPC_P4 ; 
 int /*<<< orphan*/  MPC_P5 ; 
 int /*<<< orphan*/  MPC_P6 ; 
 int /*<<< orphan*/  atm_mpoa_init_cache (struct mpoa_client*) ; 
 struct mpoa_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mpoa_client* mpcs ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mpoa_client *alloc_mpc(void)
{
	struct mpoa_client *mpc;

	mpc = kzalloc(sizeof(struct mpoa_client), GFP_KERNEL);
	if (mpc == NULL)
		return NULL;
	rwlock_init(&mpc->ingress_lock);
	rwlock_init(&mpc->egress_lock);
	mpc->next = mpcs;
	atm_mpoa_init_cache(mpc);

	mpc->parameters.mpc_p1 = MPC_P1;
	mpc->parameters.mpc_p2 = MPC_P2;
	memset(mpc->parameters.mpc_p3, 0, sizeof(mpc->parameters.mpc_p3));
	mpc->parameters.mpc_p4 = MPC_P4;
	mpc->parameters.mpc_p5 = MPC_P5;
	mpc->parameters.mpc_p6 = MPC_P6;

	mpcs = mpc;

	return mpc;
}