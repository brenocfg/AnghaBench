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
struct TYPE_2__ {int preferred_node; } ;
struct mempolicy {scalar_t__ mode; int flags; TYPE_1__ v; } ;
typedef  int gfp_t ;

/* Variables and functions */
 scalar_t__ MPOL_BIND ; 
 int MPOL_F_LOCAL ; 
 scalar_t__ MPOL_PREFERRED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __GFP_THISNODE ; 

__attribute__((used)) static int policy_node(gfp_t gfp, struct mempolicy *policy,
								int nd)
{
	if (policy->mode == MPOL_PREFERRED && !(policy->flags & MPOL_F_LOCAL))
		nd = policy->v.preferred_node;
	else {
		/*
		 * __GFP_THISNODE shouldn't even be used with the bind policy
		 * because we might easily break the expectation to stay on the
		 * requested node and not break the policy.
		 */
		WARN_ON_ONCE(policy->mode == MPOL_BIND && (gfp & __GFP_THISNODE));
	}

	return nd;
}