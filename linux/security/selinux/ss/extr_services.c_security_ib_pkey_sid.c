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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sidtab {int dummy; } ;
struct selinux_state {TYPE_3__* ss; } ;
struct policydb {struct ocontext** ocontexts; } ;
struct TYPE_4__ {scalar_t__ low_pkey; scalar_t__ high_pkey; scalar_t__ subnet_prefix; } ;
struct TYPE_5__ {TYPE_1__ ibpkey; } ;
struct ocontext {scalar_t__* sid; int /*<<< orphan*/ * context; struct ocontext* next; TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  policy_rwlock; struct sidtab* sidtab; struct policydb policydb; } ;

/* Variables and functions */
 size_t OCON_IBPKEY ; 
 scalar_t__ SECINITSID_UNLABELED ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int sidtab_context_to_sid (struct sidtab*,int /*<<< orphan*/ *,scalar_t__*) ; 

int security_ib_pkey_sid(struct selinux_state *state,
			 u64 subnet_prefix, u16 pkey_num, u32 *out_sid)
{
	struct policydb *policydb;
	struct sidtab *sidtab;
	struct ocontext *c;
	int rc = 0;

	read_lock(&state->ss->policy_rwlock);

	policydb = &state->ss->policydb;
	sidtab = state->ss->sidtab;

	c = policydb->ocontexts[OCON_IBPKEY];
	while (c) {
		if (c->u.ibpkey.low_pkey <= pkey_num &&
		    c->u.ibpkey.high_pkey >= pkey_num &&
		    c->u.ibpkey.subnet_prefix == subnet_prefix)
			break;

		c = c->next;
	}

	if (c) {
		if (!c->sid[0]) {
			rc = sidtab_context_to_sid(sidtab,
						   &c->context[0],
						   &c->sid[0]);
			if (rc)
				goto out;
		}
		*out_sid = c->sid[0];
	} else
		*out_sid = SECINITSID_UNLABELED;

out:
	read_unlock(&state->ss->policy_rwlock);
	return rc;
}