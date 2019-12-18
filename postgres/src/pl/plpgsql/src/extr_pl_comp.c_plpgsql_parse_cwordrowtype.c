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
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  PLpgSQL_type ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_rel_type_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsecond (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * makeRangeVar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  makeTypeNameFromNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * plpgsql_build_datatype (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plpgsql_compile_tmp_cxt ; 
 int /*<<< orphan*/  strVal (int /*<<< orphan*/ ) ; 

PLpgSQL_type *
plpgsql_parse_cwordrowtype(List *idents)
{
	Oid			classOid;
	RangeVar   *relvar;
	MemoryContext oldCxt;

	/*
	 * As above, this is a relation lookup but could be a type lookup if we
	 * weren't being backwards-compatible about error wording.
	 */
	if (list_length(idents) != 2)
		return NULL;

	/* Avoid memory leaks in long-term function context */
	oldCxt = MemoryContextSwitchTo(plpgsql_compile_tmp_cxt);

	/* Look up relation name.  Can't lock it - we might not have privileges. */
	relvar = makeRangeVar(strVal(linitial(idents)),
						  strVal(lsecond(idents)),
						  -1);
	classOid = RangeVarGetRelid(relvar, NoLock, false);

	MemoryContextSwitchTo(oldCxt);

	/* Build and return the row type struct */
	return plpgsql_build_datatype(get_rel_type_id(classOid), -1, InvalidOid,
								  makeTypeNameFromNameList(idents));
}