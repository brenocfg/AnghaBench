#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ baserestrict_min_security; } ;
struct TYPE_5__ {scalar_t__ security_level; scalar_t__ leakproof; } ;
typedef  TYPE_1__ RestrictInfo ;
typedef  TYPE_2__ RelOptInfo ;

/* Variables and functions */

bool
restriction_is_securely_promotable(RestrictInfo *restrictinfo,
								   RelOptInfo *rel)
{
	/*
	 * It's okay if there are no baserestrictinfo clauses for the rel that
	 * would need to go before this one, *or* if this one is leakproof.
	 */
	if (restrictinfo->security_level <= rel->baserestrict_min_security ||
		restrictinfo->leakproof)
		return true;
	else
		return false;
}