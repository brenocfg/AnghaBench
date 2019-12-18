#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct sidtab {int dummy; } ;
struct selinux_state {TYPE_4__* ss; } ;
struct policydb {struct ocontext** ocontexts; } ;
struct TYPE_6__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int addr; int mask; } ;
struct TYPE_7__ {TYPE_2__ node6; TYPE_1__ node; } ;
struct ocontext {int* sid; int /*<<< orphan*/ * context; struct ocontext* next; TYPE_3__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  policy_rwlock; struct sidtab* sidtab; struct policydb policydb; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EINVAL ; 
 size_t OCON_NODE ; 
 size_t OCON_NODE6 ; 
 int SECINITSID_NODE ; 
 int /*<<< orphan*/  match_ipv6_addrmask (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int sidtab_context_to_sid (struct sidtab*,int /*<<< orphan*/ *,int*) ; 

int security_node_sid(struct selinux_state *state,
		      u16 domain,
		      void *addrp,
		      u32 addrlen,
		      u32 *out_sid)
{
	struct policydb *policydb;
	struct sidtab *sidtab;
	int rc;
	struct ocontext *c;

	read_lock(&state->ss->policy_rwlock);

	policydb = &state->ss->policydb;
	sidtab = state->ss->sidtab;

	switch (domain) {
	case AF_INET: {
		u32 addr;

		rc = -EINVAL;
		if (addrlen != sizeof(u32))
			goto out;

		addr = *((u32 *)addrp);

		c = policydb->ocontexts[OCON_NODE];
		while (c) {
			if (c->u.node.addr == (addr & c->u.node.mask))
				break;
			c = c->next;
		}
		break;
	}

	case AF_INET6:
		rc = -EINVAL;
		if (addrlen != sizeof(u64) * 2)
			goto out;
		c = policydb->ocontexts[OCON_NODE6];
		while (c) {
			if (match_ipv6_addrmask(addrp, c->u.node6.addr,
						c->u.node6.mask))
				break;
			c = c->next;
		}
		break;

	default:
		rc = 0;
		*out_sid = SECINITSID_NODE;
		goto out;
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
	} else {
		*out_sid = SECINITSID_NODE;
	}

	rc = 0;
out:
	read_unlock(&state->ss->policy_rwlock);
	return rc;
}