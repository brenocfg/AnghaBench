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
typedef  int /*<<< orphan*/  RestrictInfo ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clause ; 
 int /*<<< orphan*/  is_pushed_down ; 
 int /*<<< orphan*/  nullable_relids ; 
 int /*<<< orphan*/  outer_relids ; 
 int /*<<< orphan*/  outerjoin_delayed ; 
 int /*<<< orphan*/  required_relids ; 
 int /*<<< orphan*/  security_level ; 

__attribute__((used)) static bool
_equalRestrictInfo(const RestrictInfo *a, const RestrictInfo *b)
{
	COMPARE_NODE_FIELD(clause);
	COMPARE_SCALAR_FIELD(is_pushed_down);
	COMPARE_SCALAR_FIELD(outerjoin_delayed);
	COMPARE_SCALAR_FIELD(security_level);
	COMPARE_BITMAPSET_FIELD(required_relids);
	COMPARE_BITMAPSET_FIELD(outer_relids);
	COMPARE_BITMAPSET_FIELD(nullable_relids);

	/*
	 * We ignore all the remaining fields, since they may not be set yet, and
	 * should be derivable from the clause anyway.
	 */

	return true;
}