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
struct sadb_prop {int sadb_prop_len; int sadb_prop_replay; struct sadb_comb* sadb_prop_reserved; int /*<<< orphan*/  sadb_prop_exttype; } ;
struct sadb_comb {int sadb_comb_hard_addtime; int sadb_comb_soft_addtime; int sadb_comb_hard_usetime; int sadb_comb_soft_usetime; int /*<<< orphan*/  sadb_comb_encrypt_maxbits; int /*<<< orphan*/  sadb_comb_encrypt_minbits; int /*<<< orphan*/  sadb_comb_encrypt; int /*<<< orphan*/  sadb_comb_auth_maxbits; int /*<<< orphan*/  sadb_comb_auth_minbits; int /*<<< orphan*/  sadb_comb_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  SADB_EXT_PROPOSAL ; 
 scalar_t__ aalg_tmpl_set (struct xfrm_tmpl const*,struct xfrm_algo_desc const*) ; 
 scalar_t__ ealg_tmpl_set (struct xfrm_tmpl const*,struct xfrm_algo_desc const*) ; 
 int /*<<< orphan*/  memset (struct sadb_comb*,int /*<<< orphan*/ ,int) ; 
 void* skb_put (struct sk_buff*,int) ; 
 struct xfrm_algo_desc* xfrm_aalg_get_byidx (int) ; 
 struct xfrm_algo_desc* xfrm_ealg_get_byidx (int) ; 

__attribute__((used)) static void dump_esp_combs(struct sk_buff *skb, const struct xfrm_tmpl *t)
{
	struct sadb_prop *p;
	int i, k;

	p = skb_put(skb, sizeof(struct sadb_prop));
	p->sadb_prop_len = sizeof(struct sadb_prop)/8;
	p->sadb_prop_exttype = SADB_EXT_PROPOSAL;
	p->sadb_prop_replay = 32;
	memset(p->sadb_prop_reserved, 0, sizeof(p->sadb_prop_reserved));

	for (i=0; ; i++) {
		const struct xfrm_algo_desc *ealg = xfrm_ealg_get_byidx(i);
		if (!ealg)
			break;

		if (!ealg->pfkey_supported)
			continue;

		if (!(ealg_tmpl_set(t, ealg) && ealg->available))
			continue;

		for (k = 1; ; k++) {
			struct sadb_comb *c;
			const struct xfrm_algo_desc *aalg = xfrm_aalg_get_byidx(k);
			if (!aalg)
				break;
			if (!aalg->pfkey_supported)
				continue;
			if (!(aalg_tmpl_set(t, aalg) && aalg->available))
				continue;
			c = skb_put(skb, sizeof(struct sadb_comb));
			memset(c, 0, sizeof(*c));
			p->sadb_prop_len += sizeof(struct sadb_comb)/8;
			c->sadb_comb_auth = aalg->desc.sadb_alg_id;
			c->sadb_comb_auth_minbits = aalg->desc.sadb_alg_minbits;
			c->sadb_comb_auth_maxbits = aalg->desc.sadb_alg_maxbits;
			c->sadb_comb_encrypt = ealg->desc.sadb_alg_id;
			c->sadb_comb_encrypt_minbits = ealg->desc.sadb_alg_minbits;
			c->sadb_comb_encrypt_maxbits = ealg->desc.sadb_alg_maxbits;
			c->sadb_comb_hard_addtime = 24*60*60;
			c->sadb_comb_soft_addtime = 20*60*60;
			c->sadb_comb_hard_usetime = 8*60*60;
			c->sadb_comb_soft_usetime = 7*60*60;
		}
	}
}