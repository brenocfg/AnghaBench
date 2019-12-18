#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  dump; TYPE_2__* namespace; } ;
struct TYPE_12__ {TYPE_3__ dobj; } ;
struct TYPE_11__ {scalar_t__ include_everything; } ;
struct TYPE_8__ {int /*<<< orphan*/  dump_contains; } ;
struct TYPE_9__ {TYPE_1__ dobj; } ;
typedef  TYPE_4__ DumpOptions ;
typedef  TYPE_5__ DefaultACLInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_COMPONENT_ALL ; 
 int /*<<< orphan*/  DUMP_COMPONENT_NONE ; 

__attribute__((used)) static void
selectDumpableDefaultACL(DefaultACLInfo *dinfo, DumpOptions *dopt)
{
	/* Default ACLs can't be extension members */

	if (dinfo->dobj.namespace)
		/* default ACLs are considered part of the namespace */
		dinfo->dobj.dump = dinfo->dobj.namespace->dobj.dump_contains;
	else
		dinfo->dobj.dump = dopt->include_everything ?
			DUMP_COMPONENT_ALL : DUMP_COMPONENT_NONE;
}