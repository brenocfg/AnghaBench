#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_usersa_id {int /*<<< orphan*/  family; int /*<<< orphan*/  proto; int /*<<< orphan*/  daddr; int /*<<< orphan*/  spi; } ;
struct xfrm_state {int dummy; } ;
struct xfrm_mark {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  IPSEC_PROTO_ANY ; 
 int /*<<< orphan*/  XFRMA_SRCADDR ; 
 int /*<<< orphan*/  verify_one_addr (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ xfrm_id_proto_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_mark_get (struct nlattr**,struct xfrm_mark*) ; 
 struct xfrm_state* xfrm_state_lookup (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfrm_state* xfrm_state_lookup_byaddr (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfrm_state *xfrm_user_state_lookup(struct net *net,
						 struct xfrm_usersa_id *p,
						 struct nlattr **attrs,
						 int *errp)
{
	struct xfrm_state *x = NULL;
	struct xfrm_mark m;
	int err;
	u32 mark = xfrm_mark_get(attrs, &m);

	if (xfrm_id_proto_match(p->proto, IPSEC_PROTO_ANY)) {
		err = -ESRCH;
		x = xfrm_state_lookup(net, mark, &p->daddr, p->spi, p->proto, p->family);
	} else {
		xfrm_address_t *saddr = NULL;

		verify_one_addr(attrs, XFRMA_SRCADDR, &saddr);
		if (!saddr) {
			err = -EINVAL;
			goto out;
		}

		err = -ESRCH;
		x = xfrm_state_lookup_byaddr(net, mark,
					     &p->daddr, saddr,
					     p->proto, p->family);
	}

 out:
	if (!x && errp)
		*errp = err;
	return x;
}