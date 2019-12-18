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
struct TYPE_14__ {int remoteVersion; TYPE_1__* dopt; } ;
struct TYPE_13__ {int ext_member; int dump; int /*<<< orphan*/  catId; } ;
struct TYPE_11__ {int dump; int dump_contains; int /*<<< orphan*/  dumpId; } ;
struct TYPE_12__ {TYPE_2__ dobj; } ;
struct TYPE_10__ {scalar_t__ binary_upgrade; } ;
typedef  TYPE_3__ ExtensionInfo ;
typedef  TYPE_4__ DumpableObject ;
typedef  TYPE_5__ Archive ;

/* Variables and functions */
 int DUMP_COMPONENT_ACL ; 
 int DUMP_COMPONENT_NONE ; 
 int DUMP_COMPONENT_POLICY ; 
 int DUMP_COMPONENT_SECLABEL ; 
 int /*<<< orphan*/  addObjectDependency (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* findOwningExtension (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
checkExtensionMembership(DumpableObject *dobj, Archive *fout)
{
	ExtensionInfo *ext = findOwningExtension(dobj->catId);

	if (ext == NULL)
		return false;

	dobj->ext_member = true;

	/* Record dependency so that getDependencies needn't deal with that */
	addObjectDependency(dobj, ext->dobj.dumpId);

	/*
	 * In 9.6 and above, mark the member object to have any non-initial ACL,
	 * policies, and security labels dumped.
	 *
	 * Note that any initial ACLs (see pg_init_privs) will be removed when we
	 * extract the information about the object.  We don't provide support for
	 * initial policies and security labels and it seems unlikely for those to
	 * ever exist, but we may have to revisit this later.
	 *
	 * Prior to 9.6, we do not include any extension member components.
	 *
	 * In binary upgrades, we still dump all components of the members
	 * individually, since the idea is to exactly reproduce the database
	 * contents rather than replace the extension contents with something
	 * different.
	 */
	if (fout->dopt->binary_upgrade)
		dobj->dump = ext->dobj.dump;
	else
	{
		if (fout->remoteVersion < 90600)
			dobj->dump = DUMP_COMPONENT_NONE;
		else
			dobj->dump = ext->dobj.dump_contains & (DUMP_COMPONENT_ACL |
													DUMP_COMPONENT_SECLABEL |
													DUMP_COMPONENT_POLICY);
	}

	return true;
}