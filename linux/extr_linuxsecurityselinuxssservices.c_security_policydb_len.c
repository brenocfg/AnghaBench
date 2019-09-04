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
struct policydb {size_t len; } ;
struct TYPE_2__ {int /*<<< orphan*/  policy_rwlock; struct policydb policydb; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

size_t security_policydb_len(struct selinux_state *state)
{
	struct policydb *p = &state->ss->policydb;
	size_t len;

	read_lock(&state->ss->policy_rwlock);
	len = p->len;
	read_unlock(&state->ss->policy_rwlock);

	return len;
}