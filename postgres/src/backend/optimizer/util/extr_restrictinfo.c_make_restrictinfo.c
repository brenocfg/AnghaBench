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
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  is_andclause (int /*<<< orphan*/ *) ; 
 scalar_t__ is_orclause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_restrictinfo_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ make_sub_restrictinfos (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RestrictInfo *
make_restrictinfo(Expr *clause,
				  bool is_pushed_down,
				  bool outerjoin_delayed,
				  bool pseudoconstant,
				  Index security_level,
				  Relids required_relids,
				  Relids outer_relids,
				  Relids nullable_relids)
{
	/*
	 * If it's an OR clause, build a modified copy with RestrictInfos inserted
	 * above each subclause of the top-level AND/OR structure.
	 */
	if (is_orclause(clause))
		return (RestrictInfo *) make_sub_restrictinfos(clause,
													   is_pushed_down,
													   outerjoin_delayed,
													   pseudoconstant,
													   security_level,
													   required_relids,
													   outer_relids,
													   nullable_relids);

	/* Shouldn't be an AND clause, else AND/OR flattening messed up */
	Assert(!is_andclause(clause));

	return make_restrictinfo_internal(clause,
									  NULL,
									  is_pushed_down,
									  outerjoin_delayed,
									  pseudoconstant,
									  security_level,
									  required_relids,
									  outer_relids,
									  nullable_relids);
}