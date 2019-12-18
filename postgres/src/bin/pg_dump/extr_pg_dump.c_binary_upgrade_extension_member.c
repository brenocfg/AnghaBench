#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nDeps; scalar_t__ objType; char const* name; int /*<<< orphan*/ * dependencies; int /*<<< orphan*/  ext_member; } ;
typedef  int /*<<< orphan*/  PQExpBuffer ;
typedef  TYPE_1__ DumpableObject ;

/* Variables and functions */
 scalar_t__ DO_EXTENSION ; 
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fatal (char*,char const*,char const*) ; 
 TYPE_1__* findObjectByDumpId (int /*<<< orphan*/ ) ; 
 char const* fmtId (char const*) ; 

__attribute__((used)) static void
binary_upgrade_extension_member(PQExpBuffer upgrade_buffer,
								DumpableObject *dobj,
								const char *objtype,
								const char *objname,
								const char *objnamespace)
{
	DumpableObject *extobj = NULL;
	int			i;

	if (!dobj->ext_member)
		return;

	/*
	 * Find the parent extension.  We could avoid this search if we wanted to
	 * add a link field to DumpableObject, but the space costs of that would
	 * be considerable.  We assume that member objects could only have a
	 * direct dependency on their own extension, not any others.
	 */
	for (i = 0; i < dobj->nDeps; i++)
	{
		extobj = findObjectByDumpId(dobj->dependencies[i]);
		if (extobj && extobj->objType == DO_EXTENSION)
			break;
		extobj = NULL;
	}
	if (extobj == NULL)
		fatal("could not find parent extension for %s %s",
			  objtype, objname);

	appendPQExpBufferStr(upgrade_buffer,
						 "\n-- For binary upgrade, handle extension membership the hard way\n");
	appendPQExpBuffer(upgrade_buffer, "ALTER EXTENSION %s ADD %s ",
					  fmtId(extobj->name),
					  objtype);
	if (objnamespace && *objnamespace)
		appendPQExpBuffer(upgrade_buffer, "%s.", fmtId(objnamespace));
	appendPQExpBuffer(upgrade_buffer, "%s;\n", objname);
}