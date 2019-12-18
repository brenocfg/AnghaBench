#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_4__ {int location; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int RTERangeTablePosn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  get_rte_attribute_type (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* makeVar (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

Var *
make_var(ParseState *pstate, RangeTblEntry *rte, int attrno, int location)
{
	Var		   *result;
	int			vnum,
				sublevels_up;
	Oid			vartypeid;
	int32		type_mod;
	Oid			varcollid;

	vnum = RTERangeTablePosn(pstate, rte, &sublevels_up);
	get_rte_attribute_type(rte, attrno, &vartypeid, &type_mod, &varcollid);
	result = makeVar(vnum, attrno, vartypeid, type_mod, varcollid, sublevels_up);
	result->location = location;
	return result;
}