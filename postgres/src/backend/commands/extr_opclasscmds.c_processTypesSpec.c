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
typedef  int /*<<< orphan*/  TypeName ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 scalar_t__ lsecond (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  typenameTypeId (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
processTypesSpec(List *args, Oid *lefttype, Oid *righttype)
{
	TypeName   *typeName;

	Assert(args != NIL);

	typeName = (TypeName *) linitial(args);
	*lefttype = typenameTypeId(NULL, typeName);

	if (list_length(args) > 1)
	{
		typeName = (TypeName *) lsecond(args);
		*righttype = typenameTypeId(NULL, typeName);
	}
	else
		*righttype = *lefttype;

	if (list_length(args) > 2)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("one or two argument types must be specified")));
}