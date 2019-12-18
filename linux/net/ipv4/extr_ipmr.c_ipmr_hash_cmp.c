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
struct rhashtable_compare_arg {struct mfc_cache_cmp_arg* key; } ;
struct mfc_cache_cmp_arg {scalar_t__ mfc_mcastgrp; scalar_t__ mfc_origin; } ;
struct mfc_cache {scalar_t__ mfc_mcastgrp; scalar_t__ mfc_origin; } ;

/* Variables and functions */

__attribute__((used)) static inline int ipmr_hash_cmp(struct rhashtable_compare_arg *arg,
				const void *ptr)
{
	const struct mfc_cache_cmp_arg *cmparg = arg->key;
	struct mfc_cache *c = (struct mfc_cache *)ptr;

	return cmparg->mfc_mcastgrp != c->mfc_mcastgrp ||
	       cmparg->mfc_origin != c->mfc_origin;
}