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
typedef  int /*<<< orphan*/  SpecialJoinInfo ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delay_upper_joins ; 
 int /*<<< orphan*/  jointype ; 
 int /*<<< orphan*/  lhs_strict ; 
 int /*<<< orphan*/  min_lefthand ; 
 int /*<<< orphan*/  min_righthand ; 
 int /*<<< orphan*/  semi_can_btree ; 
 int /*<<< orphan*/  semi_can_hash ; 
 int /*<<< orphan*/  semi_operators ; 
 int /*<<< orphan*/  semi_rhs_exprs ; 
 int /*<<< orphan*/  syn_lefthand ; 
 int /*<<< orphan*/  syn_righthand ; 

__attribute__((used)) static bool
_equalSpecialJoinInfo(const SpecialJoinInfo *a, const SpecialJoinInfo *b)
{
	COMPARE_BITMAPSET_FIELD(min_lefthand);
	COMPARE_BITMAPSET_FIELD(min_righthand);
	COMPARE_BITMAPSET_FIELD(syn_lefthand);
	COMPARE_BITMAPSET_FIELD(syn_righthand);
	COMPARE_SCALAR_FIELD(jointype);
	COMPARE_SCALAR_FIELD(lhs_strict);
	COMPARE_SCALAR_FIELD(delay_upper_joins);
	COMPARE_SCALAR_FIELD(semi_can_btree);
	COMPARE_SCALAR_FIELD(semi_can_hash);
	COMPARE_NODE_FIELD(semi_operators);
	COMPARE_NODE_FIELD(semi_rhs_exprs);

	return true;
}