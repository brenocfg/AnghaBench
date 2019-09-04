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
struct xfrm_tmpl {int dummy; } ;
struct xfrm_algo_desc {scalar_t__ available; int /*<<< orphan*/  pfkey_supported; } ;
struct sadb_prop {int dummy; } ;
struct sadb_comb {int dummy; } ;

/* Variables and functions */
 scalar_t__ aalg_tmpl_set (struct xfrm_tmpl const*,struct xfrm_algo_desc const*) ; 
 scalar_t__ ealg_tmpl_set (struct xfrm_tmpl const*,struct xfrm_algo_desc const*) ; 
 struct xfrm_algo_desc* xfrm_aalg_get_byidx (int) ; 
 struct xfrm_algo_desc* xfrm_ealg_get_byidx (int) ; 

__attribute__((used)) static int count_esp_combs(const struct xfrm_tmpl *t)
{
	int i, k, sz = 0;

	for (i = 0; ; i++) {
		const struct xfrm_algo_desc *ealg = xfrm_ealg_get_byidx(i);
		if (!ealg)
			break;

		if (!ealg->pfkey_supported)
			continue;

		if (!(ealg_tmpl_set(t, ealg) && ealg->available))
			continue;

		for (k = 1; ; k++) {
			const struct xfrm_algo_desc *aalg = xfrm_aalg_get_byidx(k);
			if (!aalg)
				break;

			if (!aalg->pfkey_supported)
				continue;

			if (aalg_tmpl_set(t, aalg) && aalg->available)
				sz += sizeof(struct sadb_comb);
		}
	}
	return sz + sizeof(struct sadb_prop);
}