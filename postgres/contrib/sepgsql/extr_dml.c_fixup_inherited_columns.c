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
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstLowInvalidHeapAttributeNumber ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,scalar_t__) ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 char* get_attname (scalar_t__,scalar_t__,int) ; 
 scalar_t__ get_attnum (scalar_t__,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static Bitmapset *
fixup_inherited_columns(Oid parentId, Oid childId, Bitmapset *columns)
{
	Bitmapset  *result = NULL;
	int			index;

	/*
	 * obviously, no need to do anything here
	 */
	if (parentId == childId)
		return columns;

	index = -1;
	while ((index = bms_next_member(columns, index)) >= 0)
	{
		/* bit numbers are offset by FirstLowInvalidHeapAttributeNumber */
		AttrNumber	attno = index + FirstLowInvalidHeapAttributeNumber;
		char	   *attname;

		/*
		 * whole-row-reference shall be fixed-up later
		 */
		if (attno == InvalidAttrNumber)
		{
			result = bms_add_member(result, index);
			continue;
		}

		attname = get_attname(parentId, attno, false);
		attno = get_attnum(childId, attname);
		if (attno == InvalidAttrNumber)
			elog(ERROR, "cache lookup failed for attribute %s of relation %u",
				 attname, childId);

		result = bms_add_member(result,
								attno - FirstLowInvalidHeapAttributeNumber);

		pfree(attname);
	}

	return result;
}