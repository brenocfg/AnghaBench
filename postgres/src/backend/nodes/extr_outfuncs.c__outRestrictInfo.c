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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  RestrictInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_join ; 
 int /*<<< orphan*/  clause ; 
 int /*<<< orphan*/  clause_relids ; 
 int /*<<< orphan*/  hashjoinoperator ; 
 int /*<<< orphan*/  is_pushed_down ; 
 int /*<<< orphan*/  leakproof ; 
 int /*<<< orphan*/  left_em ; 
 int /*<<< orphan*/  left_relids ; 
 int /*<<< orphan*/  mergeopfamilies ; 
 int /*<<< orphan*/  norm_selec ; 
 int /*<<< orphan*/  nullable_relids ; 
 int /*<<< orphan*/  orclause ; 
 int /*<<< orphan*/  outer_is_left ; 
 int /*<<< orphan*/  outer_relids ; 
 int /*<<< orphan*/  outer_selec ; 
 int /*<<< orphan*/  outerjoin_delayed ; 
 int /*<<< orphan*/  pseudoconstant ; 
 int /*<<< orphan*/  required_relids ; 
 int /*<<< orphan*/  right_em ; 
 int /*<<< orphan*/  right_relids ; 
 int /*<<< orphan*/  security_level ; 

__attribute__((used)) static void
_outRestrictInfo(StringInfo str, const RestrictInfo *node)
{
	WRITE_NODE_TYPE("RESTRICTINFO");

	/* NB: this isn't a complete set of fields */
	WRITE_NODE_FIELD(clause);
	WRITE_BOOL_FIELD(is_pushed_down);
	WRITE_BOOL_FIELD(outerjoin_delayed);
	WRITE_BOOL_FIELD(can_join);
	WRITE_BOOL_FIELD(pseudoconstant);
	WRITE_BOOL_FIELD(leakproof);
	WRITE_UINT_FIELD(security_level);
	WRITE_BITMAPSET_FIELD(clause_relids);
	WRITE_BITMAPSET_FIELD(required_relids);
	WRITE_BITMAPSET_FIELD(outer_relids);
	WRITE_BITMAPSET_FIELD(nullable_relids);
	WRITE_BITMAPSET_FIELD(left_relids);
	WRITE_BITMAPSET_FIELD(right_relids);
	WRITE_NODE_FIELD(orclause);
	/* don't write parent_ec, leads to infinite recursion in plan tree dump */
	WRITE_FLOAT_FIELD(norm_selec, "%.4f");
	WRITE_FLOAT_FIELD(outer_selec, "%.4f");
	WRITE_NODE_FIELD(mergeopfamilies);
	/* don't write left_ec, leads to infinite recursion in plan tree dump */
	/* don't write right_ec, leads to infinite recursion in plan tree dump */
	WRITE_NODE_FIELD(left_em);
	WRITE_NODE_FIELD(right_em);
	WRITE_BOOL_FIELD(outer_is_left);
	WRITE_OID_FIELD(hashjoinoperator);
}