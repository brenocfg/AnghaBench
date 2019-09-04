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
struct rhashtable_compare_arg {struct nft_rhash_cmp_arg* key; } ;
struct nft_rhash_elem {int /*<<< orphan*/  ext; } ;
struct nft_rhash_cmp_arg {int /*<<< orphan*/  genmask; TYPE_1__* set; int /*<<< orphan*/  key; } ;
struct TYPE_2__ {int /*<<< orphan*/  klen; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_set_elem_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nft_set_elem_expired (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nft_set_ext_key (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int nft_rhash_cmp(struct rhashtable_compare_arg *arg,
				const void *ptr)
{
	const struct nft_rhash_cmp_arg *x = arg->key;
	const struct nft_rhash_elem *he = ptr;

	if (memcmp(nft_set_ext_key(&he->ext), x->key, x->set->klen))
		return 1;
	if (nft_set_elem_expired(&he->ext))
		return 1;
	if (!nft_set_elem_active(&he->ext, x->genmask))
		return 1;
	return 0;
}