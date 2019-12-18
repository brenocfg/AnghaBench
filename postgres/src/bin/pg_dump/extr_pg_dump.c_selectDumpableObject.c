#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* dopt; } ;
struct TYPE_13__ {int /*<<< orphan*/  dump; TYPE_2__* namespace; } ;
struct TYPE_12__ {scalar_t__ include_everything; } ;
struct TYPE_10__ {int /*<<< orphan*/  dump_contains; } ;
struct TYPE_11__ {TYPE_1__ dobj; } ;
typedef  TYPE_4__ DumpableObject ;
typedef  TYPE_5__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_COMPONENT_ALL ; 
 int /*<<< orphan*/  DUMP_COMPONENT_NONE ; 
 scalar_t__ checkExtensionMembership (TYPE_4__*,TYPE_5__*) ; 

__attribute__((used)) static void
selectDumpableObject(DumpableObject *dobj, Archive *fout)
{
	if (checkExtensionMembership(dobj, fout))
		return;					/* extension membership overrides all else */

	/*
	 * Default policy is to dump if parent namespace is dumpable, or for
	 * non-namespace-associated items, dump if we're dumping "everything".
	 */
	if (dobj->namespace)
		dobj->dump = dobj->namespace->dobj.dump_contains;
	else
		dobj->dump = fout->dopt->include_everything ?
			DUMP_COMPONENT_ALL : DUMP_COMPONENT_NONE;
}