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
struct selinux_state {TYPE_1__* ss; } ;
struct selinux_kernel_status {int policyload; int deny_unknown; int /*<<< orphan*/  sequence; } ;
struct TYPE_2__ {int /*<<< orphan*/  status_lock; scalar_t__ status_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct selinux_kernel_status* page_address (scalar_t__) ; 
 int /*<<< orphan*/  security_get_allow_unknown (struct selinux_state*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void selinux_status_update_policyload(struct selinux_state *state,
				      int seqno)
{
	struct selinux_kernel_status   *status;

	mutex_lock(&state->ss->status_lock);
	if (state->ss->status_page) {
		status = page_address(state->ss->status_page);

		status->sequence++;
		smp_wmb();

		status->policyload = seqno;
		status->deny_unknown = !security_get_allow_unknown(state);

		smp_wmb();
		status->sequence++;
	}
	mutex_unlock(&state->ss->status_lock);
}