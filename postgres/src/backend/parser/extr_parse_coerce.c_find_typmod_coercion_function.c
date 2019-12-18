#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_4__ {scalar_t__ castfunc; } ;
struct TYPE_3__ {scalar_t__ typelem; int typlen; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_type ;
typedef  TYPE_2__* Form_pg_cast ;
typedef  int /*<<< orphan*/  CoercionPathType ;

/* Variables and functions */
 int /*<<< orphan*/  CASTSOURCETARGET ; 
 int /*<<< orphan*/  COERCION_PATH_ARRAYCOERCE ; 
 int /*<<< orphan*/  COERCION_PATH_FUNC ; 
 int /*<<< orphan*/  COERCION_PATH_NONE ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typeidType (scalar_t__) ; 

CoercionPathType
find_typmod_coercion_function(Oid typeId,
							  Oid *funcid)
{
	CoercionPathType result;
	Type		targetType;
	Form_pg_type typeForm;
	HeapTuple	tuple;

	*funcid = InvalidOid;
	result = COERCION_PATH_FUNC;

	targetType = typeidType(typeId);
	typeForm = (Form_pg_type) GETSTRUCT(targetType);

	/* Check for a varlena array type */
	if (typeForm->typelem != InvalidOid && typeForm->typlen == -1)
	{
		/* Yes, switch our attention to the element type */
		typeId = typeForm->typelem;
		result = COERCION_PATH_ARRAYCOERCE;
	}
	ReleaseSysCache(targetType);

	/* Look in pg_cast */
	tuple = SearchSysCache2(CASTSOURCETARGET,
							ObjectIdGetDatum(typeId),
							ObjectIdGetDatum(typeId));

	if (HeapTupleIsValid(tuple))
	{
		Form_pg_cast castForm = (Form_pg_cast) GETSTRUCT(tuple);

		*funcid = castForm->castfunc;
		ReleaseSysCache(tuple);
	}

	if (!OidIsValid(*funcid))
		result = COERCION_PATH_NONE;

	return result;
}