#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char oprkind; scalar_t__ oprresult; int /*<<< orphan*/  oprright; int /*<<< orphan*/  oprleft; } ;
struct TYPE_7__ {int /*<<< orphan*/  amcanorderbyop; } ;
struct TYPE_6__ {int /*<<< orphan*/  righttype; int /*<<< orphan*/  lefttype; int /*<<< orphan*/  sortfamily; int /*<<< orphan*/  object; } ;
typedef  int /*<<< orphan*/  Operator ;
typedef  TYPE_1__ OpFamilyMember ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ IndexAmRoutine ;
typedef  TYPE_3__* Form_pg_operator ;

/* Variables and functions */
 scalar_t__ BOOLOID ; 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 TYPE_2__* GetIndexAmRoutineByAmId (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEROID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_am_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
assignOperTypes(OpFamilyMember *member, Oid amoid, Oid typeoid)
{
	Operator	optup;
	Form_pg_operator opform;

	/* Fetch the operator definition */
	optup = SearchSysCache1(OPEROID, ObjectIdGetDatum(member->object));
	if (!HeapTupleIsValid(optup))
		elog(ERROR, "cache lookup failed for operator %u", member->object);
	opform = (Form_pg_operator) GETSTRUCT(optup);

	/*
	 * Opfamily operators must be binary.
	 */
	if (opform->oprkind != 'b')
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("index operators must be binary")));

	if (OidIsValid(member->sortfamily))
	{
		/*
		 * Ordering op, check index supports that.  (We could perhaps also
		 * check that the operator returns a type supported by the sortfamily,
		 * but that seems more trouble than it's worth here.  If it does not,
		 * the operator will never be matchable to any ORDER BY clause, but no
		 * worse consequences can ensue.  Also, trying to check that would
		 * create an ordering hazard during dump/reload: it's possible that
		 * the family has been created but not yet populated with the required
		 * operators.)
		 */
		IndexAmRoutine *amroutine = GetIndexAmRoutineByAmId(amoid, false);

		if (!amroutine->amcanorderbyop)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
					 errmsg("access method \"%s\" does not support ordering operators",
							get_am_name(amoid))));
	}
	else
	{
		/*
		 * Search operators must return boolean.
		 */
		if (opform->oprresult != BOOLOID)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
					 errmsg("index search operators must return boolean")));
	}

	/*
	 * If lefttype/righttype isn't specified, use the operator's input types
	 */
	if (!OidIsValid(member->lefttype))
		member->lefttype = opform->oprleft;
	if (!OidIsValid(member->righttype))
		member->righttype = opform->oprright;

	ReleaseSysCache(optup);
}