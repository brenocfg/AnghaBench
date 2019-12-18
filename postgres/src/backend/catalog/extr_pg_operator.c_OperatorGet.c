#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  oprcode; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_operator ;

/* Variables and functions */
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  OPERNAMENSP ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int RegProcedureIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
OperatorGet(const char *operatorName,
			Oid operatorNamespace,
			Oid leftObjectId,
			Oid rightObjectId,
			bool *defined)
{
	HeapTuple	tup;
	Oid			operatorObjectId;

	tup = SearchSysCache4(OPERNAMENSP,
						  PointerGetDatum(operatorName),
						  ObjectIdGetDatum(leftObjectId),
						  ObjectIdGetDatum(rightObjectId),
						  ObjectIdGetDatum(operatorNamespace));
	if (HeapTupleIsValid(tup))
	{
		Form_pg_operator oprform = (Form_pg_operator) GETSTRUCT(tup);

		operatorObjectId = oprform->oid;
		*defined = RegProcedureIsValid(oprform->oprcode);
		ReleaseSysCache(tup);
	}
	else
	{
		operatorObjectId = InvalidOid;
		*defined = false;
	}

	return operatorObjectId;
}