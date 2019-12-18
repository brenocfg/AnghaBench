#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * head; } ;
struct TYPE_16__ {int /*<<< orphan*/ * head; } ;
struct TYPE_15__ {int remoteVersion; } ;
struct TYPE_13__ {int /*<<< orphan*/  oid; } ;
struct TYPE_12__ {void* dump; void* dump_contains; TYPE_1__ catId; int /*<<< orphan*/  name; } ;
struct TYPE_14__ {TYPE_10__ dobj; } ;
typedef  TYPE_2__ NamespaceInfo ;
typedef  TYPE_3__ Archive ;

/* Variables and functions */
 void* DUMP_COMPONENT_ACL ; 
 void* DUMP_COMPONENT_ALL ; 
 void* DUMP_COMPONENT_NONE ; 
 int /*<<< orphan*/  checkExtensionMembership (TYPE_10__*,TYPE_3__*) ; 
 TYPE_5__ schema_exclude_oids ; 
 TYPE_5__ schema_include_oids ; 
 scalar_t__ simple_oid_list_member (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_4__ table_include_oids ; 

__attribute__((used)) static void
selectDumpableNamespace(NamespaceInfo *nsinfo, Archive *fout)
{
	/*
	 * If specific tables are being dumped, do not dump any complete
	 * namespaces. If specific namespaces are being dumped, dump just those
	 * namespaces. Otherwise, dump all non-system namespaces.
	 */
	if (table_include_oids.head != NULL)
		nsinfo->dobj.dump_contains = nsinfo->dobj.dump = DUMP_COMPONENT_NONE;
	else if (schema_include_oids.head != NULL)
		nsinfo->dobj.dump_contains = nsinfo->dobj.dump =
			simple_oid_list_member(&schema_include_oids,
								   nsinfo->dobj.catId.oid) ?
			DUMP_COMPONENT_ALL : DUMP_COMPONENT_NONE;
	else if (fout->remoteVersion >= 90600 &&
			 strcmp(nsinfo->dobj.name, "pg_catalog") == 0)
	{
		/*
		 * In 9.6 and above, we dump out any ACLs defined in pg_catalog, if
		 * they are interesting (and not the original ACLs which were set at
		 * initdb time, see pg_init_privs).
		 */
		nsinfo->dobj.dump_contains = nsinfo->dobj.dump = DUMP_COMPONENT_ACL;
	}
	else if (strncmp(nsinfo->dobj.name, "pg_", 3) == 0 ||
			 strcmp(nsinfo->dobj.name, "information_schema") == 0)
	{
		/* Other system schemas don't get dumped */
		nsinfo->dobj.dump_contains = nsinfo->dobj.dump = DUMP_COMPONENT_NONE;
	}
	else if (strcmp(nsinfo->dobj.name, "public") == 0)
	{
		/*
		 * The public schema is a strange beast that sits in a sort of
		 * no-mans-land between being a system object and a user object.  We
		 * don't want to dump creation or comment commands for it, because
		 * that complicates matters for non-superuser use of pg_dump.  But we
		 * should dump any ACL changes that have occurred for it, and of
		 * course we should dump contained objects.
		 */
		nsinfo->dobj.dump = DUMP_COMPONENT_ACL;
		nsinfo->dobj.dump_contains = DUMP_COMPONENT_ALL;
	}
	else
		nsinfo->dobj.dump_contains = nsinfo->dobj.dump = DUMP_COMPONENT_ALL;

	/*
	 * In any case, a namespace can be excluded by an exclusion switch
	 */
	if (nsinfo->dobj.dump_contains &&
		simple_oid_list_member(&schema_exclude_oids,
							   nsinfo->dobj.catId.oid))
		nsinfo->dobj.dump_contains = nsinfo->dobj.dump = DUMP_COMPONENT_NONE;

	/*
	 * If the schema belongs to an extension, allow extension membership to
	 * override the dump decision for the schema itself.  However, this does
	 * not change dump_contains, so this won't change what we do with objects
	 * within the schema.  (If they belong to the extension, they'll get
	 * suppressed by it, otherwise not.)
	 */
	(void) checkExtensionMembership(&nsinfo->dobj, fout);
}