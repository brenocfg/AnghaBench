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
struct mfc_cache_cmp_arg {int /*<<< orphan*/  mfc_origin; int /*<<< orphan*/  mfc_mcastgrp; } ;
struct mfc_cache {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct mfc_cache* mr_mfc_find (struct mr_table*,struct mfc_cache_cmp_arg*) ; 

__attribute__((used)) static struct mfc_cache *ipmr_cache_find(struct mr_table *mrt,
					 __be32 origin,
					 __be32 mcastgrp)
{
	struct mfc_cache_cmp_arg arg = {
			.mfc_mcastgrp = mcastgrp,
			.mfc_origin = origin
	};

	return mr_mfc_find(mrt, &arg);
}