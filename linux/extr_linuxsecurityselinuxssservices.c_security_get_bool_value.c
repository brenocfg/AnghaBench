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
struct selinux_state {TYPE_2__* ss; } ;
struct TYPE_6__ {int nprim; } ;
struct policydb {TYPE_1__** bool_val_to_struct; TYPE_3__ p_bools; } ;
struct TYPE_5__ {int /*<<< orphan*/  policy_rwlock; struct policydb policydb; } ;
struct TYPE_4__ {int state; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int security_get_bool_value(struct selinux_state *state,
			    int index)
{
	struct policydb *policydb;
	int rc;
	int len;

	read_lock(&state->ss->policy_rwlock);

	policydb = &state->ss->policydb;

	rc = -EFAULT;
	len = policydb->p_bools.nprim;
	if (index >= len)
		goto out;

	rc = policydb->bool_val_to_struct[index]->state;
out:
	read_unlock(&state->ss->policy_rwlock);
	return rc;
}