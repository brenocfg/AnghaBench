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
struct mfc_cache_cmp_arg {scalar_t__ mfc_mcastgrp; scalar_t__ mfc_origin; } ;
struct mfc_cache {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 struct mfc_cache* mr_mfc_find_any (struct mr_table*,int,struct mfc_cache_cmp_arg*) ; 
 struct mfc_cache* mr_mfc_find_any_parent (struct mr_table*,int) ; 

__attribute__((used)) static struct mfc_cache *ipmr_cache_find_any(struct mr_table *mrt,
					     __be32 mcastgrp, int vifi)
{
	struct mfc_cache_cmp_arg arg = {
			.mfc_mcastgrp = mcastgrp,
			.mfc_origin = htonl(INADDR_ANY)
	};

	if (mcastgrp == htonl(INADDR_ANY))
		return mr_mfc_find_any_parent(mrt, vifi);
	return mr_mfc_find_any(mrt, vifi, &arg);
}