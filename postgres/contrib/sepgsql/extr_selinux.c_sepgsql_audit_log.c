#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long uint32 ;
typedef  size_t uint16 ;
struct TYPE_9__ {char* class_name; TYPE_1__* av; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {char* av_name; } ;
typedef  TYPE_2__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LOG ; 
 size_t SEPG_CLASS_MAX ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,char const*,...) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 TYPE_3__* selinux_catalog ; 

void
sepgsql_audit_log(bool denied,
				  const char *scontext,
				  const char *tcontext,
				  uint16 tclass,
				  uint32 audited,
				  const char *audit_name)
{
	StringInfoData buf;
	const char *class_name;
	const char *av_name;
	int			i;

	/* lookup name of the object class */
	Assert(tclass < SEPG_CLASS_MAX);
	class_name = selinux_catalog[tclass].class_name;

	/* lookup name of the permissions */
	initStringInfo(&buf);
	appendStringInfo(&buf, "%s {",
					 (denied ? "denied" : "allowed"));
	for (i = 0; selinux_catalog[tclass].av[i].av_name; i++)
	{
		if (audited & (1UL << i))
		{
			av_name = selinux_catalog[tclass].av[i].av_name;
			appendStringInfo(&buf, " %s", av_name);
		}
	}
	appendStringInfoString(&buf, " }");

	/*
	 * Call external audit module, if loaded
	 */
	appendStringInfo(&buf, " scontext=%s tcontext=%s tclass=%s",
					 scontext, tcontext, class_name);
	if (audit_name)
		appendStringInfo(&buf, " name=\"%s\"", audit_name);

	ereport(LOG, (errmsg("SELinux: %s", buf.data)));
}