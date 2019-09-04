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
struct xfrm_tmpl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sadb_alg_maxbits; int /*<<< orphan*/  sadb_alg_minbits; int /*<<< orphan*/  sadb_alg_id; } ;
struct xfrm_algo_desc {TYPE_1__ desc; scalar_t__ available; int /*<<< orphan*/  pfkey_supported; } ;
struct sk_buff {int dummy; } ;
struct sadb_prop {int sadb_prop_len; int sadb_prop_replay; int /*<<< orphan*/  sadb_prop_reserved; int /*<<< orphan*/  sadb_prop_exttype; } ;
struct sadb_comb {int sadb_comb_hard_addtime; int sadb_comb_soft_addtime; int sadb_comb_hard_usetime; int sadb_comb_soft_usetime; int /*<<< orphan*/  sadb_comb_auth_maxbits; int /*<<< orphan*/  sadb_comb_auth_minbits; int /*<<< orphan*/  sadb_comb_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  SADB_EXT_PROPOSAL ; 
 scalar_t__ aalg_tmpl_set (struct xfrm_tmpl const*,struct xfrm_algo_desc const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sadb_prop* skb_put (struct sk_buff*,int) ; 
 struct sadb_comb* skb_put_zero (struct sk_buff*,int) ; 
 struct xfrm_algo_desc* xfrm_aalg_get_byidx (int) ; 

__attribute__((used)) static void dump_ah_combs(struct sk_buff *skb, const struct xfrm_tmpl *t)
{
	struct sadb_prop *p;
	int i;

	p = skb_put(skb, sizeof(struct sadb_prop));
	p->sadb_prop_len = sizeof(struct sadb_prop)/8;
	p->sadb_prop_exttype = SADB_EXT_PROPOSAL;
	p->sadb_prop_replay = 32;
	memset(p->sadb_prop_reserved, 0, sizeof(p->sadb_prop_reserved));

	for (i = 0; ; i++) {
		const struct xfrm_algo_desc *aalg = xfrm_aalg_get_byidx(i);
		if (!aalg)
			break;

		if (!aalg->pfkey_supported)
			continue;

		if (aalg_tmpl_set(t, aalg) && aalg->available) {
			struct sadb_comb *c;
			c = skb_put_zero(skb, sizeof(struct sadb_comb));
			p->sadb_prop_len += sizeof(struct sadb_comb)/8;
			c->sadb_comb_auth = aalg->desc.sadb_alg_id;
			c->sadb_comb_auth_minbits = aalg->desc.sadb_alg_minbits;
			c->sadb_comb_auth_maxbits = aalg->desc.sadb_alg_maxbits;
			c->sadb_comb_hard_addtime = 24*60*60;
			c->sadb_comb_soft_addtime = 20*60*60;
			c->sadb_comb_hard_usetime = 8*60*60;
			c->sadb_comb_soft_usetime = 7*60*60;
		}
	}
}