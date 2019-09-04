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
struct cnic_sock {int /*<<< orphan*/  flags; scalar_t__ context; } ;
struct bnx2i_endpoint {int /*<<< orphan*/  ofld_wait; void* state; TYPE_1__* hba; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_STATE_GOING_DOWN ; 
 void* EP_STATE_CONNECT_COMPL ; 
 void* EP_STATE_CONNECT_FAILED ; 
 int /*<<< orphan*/  SK_F_OFFLD_COMPLETE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2i_cm_connect_cmpl(struct cnic_sock *cm_sk)
{
	struct bnx2i_endpoint *ep = (struct bnx2i_endpoint *) cm_sk->context;

	if (test_bit(ADAPTER_STATE_GOING_DOWN, &ep->hba->adapter_state))
		ep->state = EP_STATE_CONNECT_FAILED;
	else if (test_bit(SK_F_OFFLD_COMPLETE, &cm_sk->flags))
		ep->state = EP_STATE_CONNECT_COMPL;
	else
		ep->state = EP_STATE_CONNECT_FAILED;

	wake_up_interruptible(&ep->ofld_wait);
}