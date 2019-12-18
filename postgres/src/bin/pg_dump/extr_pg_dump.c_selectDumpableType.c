#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* namespace; int /*<<< orphan*/  dump; void* objType; } ;
struct TYPE_12__ {scalar_t__ typrelkind; TYPE_8__ dobj; scalar_t__ isArray; int /*<<< orphan*/  typrelid; } ;
typedef  TYPE_4__ TypeInfo ;
struct TYPE_9__ {int /*<<< orphan*/  dump; } ;
struct TYPE_13__ {TYPE_1__ dobj; } ;
typedef  TYPE_5__ TableInfo ;
struct TYPE_10__ {int /*<<< orphan*/  dump_contains; } ;
struct TYPE_11__ {TYPE_2__ dobj; } ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 void* DO_DUMMY_TYPE ; 
 int /*<<< orphan*/  DUMP_COMPONENT_NONE ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_COMPOSITE_TYPE ; 
 scalar_t__ checkExtensionMembership (TYPE_8__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* findTableByOid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
selectDumpableType(TypeInfo *tyinfo, Archive *fout)
{
	/* skip complex types, except for standalone composite types */
	if (OidIsValid(tyinfo->typrelid) &&
		tyinfo->typrelkind != RELKIND_COMPOSITE_TYPE)
	{
		TableInfo  *tytable = findTableByOid(tyinfo->typrelid);

		tyinfo->dobj.objType = DO_DUMMY_TYPE;
		if (tytable != NULL)
			tyinfo->dobj.dump = tytable->dobj.dump;
		else
			tyinfo->dobj.dump = DUMP_COMPONENT_NONE;
		return;
	}

	/* skip auto-generated array types */
	if (tyinfo->isArray)
	{
		tyinfo->dobj.objType = DO_DUMMY_TYPE;

		/*
		 * Fall through to set the dump flag; we assume that the subsequent
		 * rules will do the same thing as they would for the array's base
		 * type.  (We cannot reliably look up the base type here, since
		 * getTypes may not have processed it yet.)
		 */
	}

	if (checkExtensionMembership(&tyinfo->dobj, fout))
		return;					/* extension membership overrides all else */

	/* Dump based on if the contents of the namespace are being dumped */
	tyinfo->dobj.dump = tyinfo->dobj.namespace->dobj.dump_contains;
}