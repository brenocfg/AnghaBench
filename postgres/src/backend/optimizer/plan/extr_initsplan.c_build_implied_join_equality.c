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
typedef  int /*<<< orphan*/  Relids ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  BOOLOID ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  check_hashjoinable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_mergejoinable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_opclause (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_restrictinfo (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

RestrictInfo *
build_implied_join_equality(Oid opno,
							Oid collation,
							Expr *item1,
							Expr *item2,
							Relids qualscope,
							Relids nullable_relids,
							Index security_level)
{
	RestrictInfo *restrictinfo;
	Expr	   *clause;

	/*
	 * Build the new clause.  Copy to ensure it shares no substructure with
	 * original (this is necessary in case there are subselects in there...)
	 */
	clause = make_opclause(opno,
						   BOOLOID, /* opresulttype */
						   false,	/* opretset */
						   copyObject(item1),
						   copyObject(item2),
						   InvalidOid,
						   collation);

	/*
	 * Build the RestrictInfo node itself.
	 */
	restrictinfo = make_restrictinfo(clause,
									 true,	/* is_pushed_down */
									 false, /* outerjoin_delayed */
									 false, /* pseudoconstant */
									 security_level,	/* security_level */
									 qualscope, /* required_relids */
									 NULL,	/* outer_relids */
									 nullable_relids);	/* nullable_relids */

	/* Set mergejoinability/hashjoinability flags */
	check_mergejoinable(restrictinfo);
	check_hashjoinable(restrictinfo);

	return restrictinfo;
}