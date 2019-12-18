#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int same_subexprs_refutes; int same_subexprs_implies; } ;
typedef  TYPE_1__ OprProofCacheEntry ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 TYPE_1__* lookup_proof_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
operator_same_subexprs_lookup(Oid pred_op, Oid clause_op, bool refute_it)
{
	OprProofCacheEntry *cache_entry;

	cache_entry = lookup_proof_cache(pred_op, clause_op, refute_it);
	if (refute_it)
		return cache_entry->same_subexprs_refutes;
	else
		return cache_entry->same_subexprs_implies;
}