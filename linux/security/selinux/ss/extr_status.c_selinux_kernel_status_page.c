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
struct selinux_kernel_status {int deny_unknown; scalar_t__ policyload; int /*<<< orphan*/  enforcing; scalar_t__ sequence; int /*<<< orphan*/  version; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status_lock; struct page* status_page; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SELINUX_KERNEL_STATUS_VERSION ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  enforcing_enabled (struct selinux_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct selinux_kernel_status* page_address (struct page*) ; 
 int /*<<< orphan*/  security_get_allow_unknown (struct selinux_state*) ; 

struct page *selinux_kernel_status_page(struct selinux_state *state)
{
	struct selinux_kernel_status   *status;
	struct page		       *result = NULL;

	mutex_lock(&state->ss->status_lock);
	if (!state->ss->status_page) {
		state->ss->status_page = alloc_page(GFP_KERNEL|__GFP_ZERO);

		if (state->ss->status_page) {
			status = page_address(state->ss->status_page);

			status->version = SELINUX_KERNEL_STATUS_VERSION;
			status->sequence = 0;
			status->enforcing = enforcing_enabled(state);
			/*
			 * NOTE: the next policyload event shall set
			 * a positive value on the status->policyload,
			 * although it may not be 1, but never zero.
			 * So, application can know it was updated.
			 */
			status->policyload = 0;
			status->deny_unknown =
				!security_get_allow_unknown(state);
		}
	}
	result = state->ss->status_page;
	mutex_unlock(&state->ss->status_lock);

	return result;
}