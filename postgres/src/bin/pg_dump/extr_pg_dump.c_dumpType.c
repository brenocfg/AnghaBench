#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dump; } ;
struct TYPE_20__ {scalar_t__ typtype; TYPE_1__ dobj; int /*<<< orphan*/  isDefined; } ;
typedef  TYPE_2__ TypeInfo ;
struct TYPE_22__ {TYPE_3__* dopt; } ;
struct TYPE_21__ {scalar_t__ dataOnly; } ;
typedef  TYPE_3__ DumpOptions ;
typedef  TYPE_4__ Archive ;

/* Variables and functions */
 scalar_t__ TYPTYPE_BASE ; 
 scalar_t__ TYPTYPE_COMPOSITE ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 scalar_t__ TYPTYPE_ENUM ; 
 scalar_t__ TYPTYPE_PSEUDO ; 
 scalar_t__ TYPTYPE_RANGE ; 
 int /*<<< orphan*/  dumpBaseType (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dumpCompositeType (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dumpDomain (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dumpEnumType (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dumpRangeType (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dumpUndefinedType (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pg_log_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dumpType(Archive *fout, TypeInfo *tyinfo)
{
	DumpOptions *dopt = fout->dopt;

	/* Skip if not to be dumped */
	if (!tyinfo->dobj.dump || dopt->dataOnly)
		return;

	/* Dump out in proper style */
	if (tyinfo->typtype == TYPTYPE_BASE)
		dumpBaseType(fout, tyinfo);
	else if (tyinfo->typtype == TYPTYPE_DOMAIN)
		dumpDomain(fout, tyinfo);
	else if (tyinfo->typtype == TYPTYPE_COMPOSITE)
		dumpCompositeType(fout, tyinfo);
	else if (tyinfo->typtype == TYPTYPE_ENUM)
		dumpEnumType(fout, tyinfo);
	else if (tyinfo->typtype == TYPTYPE_RANGE)
		dumpRangeType(fout, tyinfo);
	else if (tyinfo->typtype == TYPTYPE_PSEUDO && !tyinfo->isDefined)
		dumpUndefinedType(fout, tyinfo);
	else
		pg_log_warning("typtype of data type \"%s\" appears to be invalid",
					   tyinfo->dobj.name);
}