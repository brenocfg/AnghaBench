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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  BTREE_AM_OID ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetDefaultOpClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsBinaryCoercible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 char* NameListToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*,char*) ; 
 char* format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opclass_input_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opclass_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Oid
findRangeSubOpclass(List *opcname, Oid subtype)
{
	Oid			opcid;
	Oid			opInputType;

	if (opcname != NIL)
	{
		opcid = get_opclass_oid(BTREE_AM_OID, opcname, false);

		/*
		 * Verify that the operator class accepts this datatype. Note we will
		 * accept binary compatibility.
		 */
		opInputType = get_opclass_input_type(opcid);
		if (!IsBinaryCoercible(subtype, opInputType))
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("operator class \"%s\" does not accept data type %s",
							NameListToString(opcname),
							format_type_be(subtype))));
	}
	else
	{
		opcid = GetDefaultOpClass(subtype, BTREE_AM_OID);
		if (!OidIsValid(opcid))
		{
			/* We spell the error message identically to ResolveOpClass */
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("data type %s has no default operator class for access method \"%s\"",
							format_type_be(subtype), "btree"),
					 errhint("You must specify an operator class for the range type or define a default operator class for the subtype.")));
		}
	}

	return opcid;
}