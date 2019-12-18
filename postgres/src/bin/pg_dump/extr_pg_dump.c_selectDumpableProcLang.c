#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ oid; } ;
struct TYPE_13__ {void* dump; TYPE_2__ catId; } ;
struct TYPE_12__ {int remoteVersion; TYPE_1__* dopt; } ;
struct TYPE_11__ {TYPE_7__ dobj; } ;
struct TYPE_9__ {int /*<<< orphan*/  include_everything; } ;
typedef  TYPE_3__ ProcLangInfo ;
typedef  scalar_t__ Oid ;
typedef  TYPE_4__ Archive ;

/* Variables and functions */
 void* DUMP_COMPONENT_ACL ; 
 void* DUMP_COMPONENT_ALL ; 
 void* DUMP_COMPONENT_NONE ; 
 scalar_t__ checkExtensionMembership (TYPE_7__*,TYPE_4__*) ; 
 scalar_t__ g_last_builtin_oid ; 

__attribute__((used)) static void
selectDumpableProcLang(ProcLangInfo *plang, Archive *fout)
{
	if (checkExtensionMembership(&plang->dobj, fout))
		return;					/* extension membership overrides all else */

	/*
	 * Only include procedural languages when we are dumping everything.
	 *
	 * For from-initdb procedural languages, only include ACLs, as we do for
	 * the pg_catalog namespace.  We need this because procedural languages do
	 * not live in any namespace.
	 */
	if (!fout->dopt->include_everything)
		plang->dobj.dump = DUMP_COMPONENT_NONE;
	else
	{
		if (plang->dobj.catId.oid <= (Oid) g_last_builtin_oid)
			plang->dobj.dump = fout->remoteVersion < 90600 ?
				DUMP_COMPONENT_NONE : DUMP_COMPONENT_ACL;
		else
			plang->dobj.dump = DUMP_COMPONENT_ALL;
	}
}