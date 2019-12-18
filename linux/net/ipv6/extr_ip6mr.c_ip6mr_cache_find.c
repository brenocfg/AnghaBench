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
struct mr_table {int dummy; } ;
struct in6_addr {int dummy; } ;
struct mfc6_cache_cmp_arg {struct in6_addr const mf6c_mcastgrp; struct in6_addr const mf6c_origin; } ;
struct mfc6_cache {int dummy; } ;

/* Variables and functions */
 struct mfc6_cache* mr_mfc_find (struct mr_table*,struct mfc6_cache_cmp_arg*) ; 

__attribute__((used)) static struct mfc6_cache *ip6mr_cache_find(struct mr_table *mrt,
					   const struct in6_addr *origin,
					   const struct in6_addr *mcastgrp)
{
	struct mfc6_cache_cmp_arg arg = {
		.mf6c_origin = *origin,
		.mf6c_mcastgrp = *mcastgrp,
	};

	return mr_mfc_find(mrt, &arg);
}