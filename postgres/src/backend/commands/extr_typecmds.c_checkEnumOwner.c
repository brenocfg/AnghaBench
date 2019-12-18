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
struct TYPE_2__ {scalar_t__ typtype; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserId () ; 
 scalar_t__ TYPTYPE_ENUM ; 
 int /*<<< orphan*/  aclcheck_error_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_type_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
checkEnumOwner(HeapTuple tup)
{
	Form_pg_type typTup = (Form_pg_type) GETSTRUCT(tup);

	/* Check that this is actually an enum */
	if (typTup->typtype != TYPTYPE_ENUM)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("%s is not an enum",
						format_type_be(typTup->oid))));

	/* Permission check: must own type */
	if (!pg_type_ownercheck(typTup->oid, GetUserId()))
		aclcheck_error_type(ACLCHECK_NOT_OWNER, typTup->oid);
}