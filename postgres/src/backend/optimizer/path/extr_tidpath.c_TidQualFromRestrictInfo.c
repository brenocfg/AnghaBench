#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pseudoconstant; } ;
typedef  TYPE_1__ RestrictInfo ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ IsCurrentOfClause (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IsTidEqualAnyClause (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IsTidEqualClause (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * list_make1 (TYPE_1__*) ; 
 int /*<<< orphan*/  restriction_is_securely_promotable (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
TidQualFromRestrictInfo(RestrictInfo *rinfo, RelOptInfo *rel)
{
	/*
	 * We may ignore pseudoconstant clauses (they can't contain Vars, so could
	 * not match anyway).
	 */
	if (rinfo->pseudoconstant)
		return NIL;

	/*
	 * If clause must wait till after some lower-security-level restriction
	 * clause, reject it.
	 */
	if (!restriction_is_securely_promotable(rinfo, rel))
		return NIL;

	/*
	 * Check all base cases.  If we get a match, return the clause.
	 */
	if (IsTidEqualClause(rinfo, rel) ||
		IsTidEqualAnyClause(rinfo, rel) ||
		IsCurrentOfClause(rinfo, rel))
		return list_make1(rinfo);

	return NIL;
}