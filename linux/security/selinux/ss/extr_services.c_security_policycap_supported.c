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
struct policydb {int /*<<< orphan*/  policycaps; } ;
struct TYPE_2__ {int /*<<< orphan*/  policy_rwlock; struct policydb policydb; } ;

/* Variables and functions */
 int ebitmap_get_bit (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int security_policycap_supported(struct selinux_state *state,
				 unsigned int req_cap)
{
	struct policydb *policydb = &state->ss->policydb;
	int rc;

	read_lock(&state->ss->policy_rwlock);
	rc = ebitmap_get_bit(&policydb->policycaps, req_cap);
	read_unlock(&state->ss->policy_rwlock);

	return rc;
}