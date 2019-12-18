#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  namespace; } ;
typedef  TYPE_2__ TocEntry ;
struct TYPE_9__ {TYPE_3__* ropt; } ;
struct TYPE_12__ {TYPE_1__ public; } ;
struct TYPE_11__ {int /*<<< orphan*/  superuser; int /*<<< orphan*/  disable_triggers; int /*<<< orphan*/  dataOnly; } ;
typedef  TYPE_3__ RestoreOptions ;
typedef  TYPE_4__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  _becomeUser (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahprintf (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmtQualifiedId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_enableTriggersIfNecessary(ArchiveHandle *AH, TocEntry *te)
{
	RestoreOptions *ropt = AH->public.ropt;

	/* This hack is only needed in a data-only restore */
	if (!ropt->dataOnly || !ropt->disable_triggers)
		return;

	pg_log_info("enabling triggers for %s", te->tag);

	/*
	 * Become superuser if possible, since they are the only ones who can
	 * disable constraint triggers.  If -S was not given, assume the initial
	 * user identity is a superuser.  (XXX would it be better to become the
	 * table owner?)
	 */
	_becomeUser(AH, ropt->superuser);

	/*
	 * Enable them.
	 */
	ahprintf(AH, "ALTER TABLE %s ENABLE TRIGGER ALL;\n\n",
			 fmtQualifiedId(te->namespace, te->tag));
}