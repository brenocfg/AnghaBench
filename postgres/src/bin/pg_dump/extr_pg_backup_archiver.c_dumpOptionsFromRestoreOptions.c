#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sequence_data; int /*<<< orphan*/  enable_row_security; int /*<<< orphan*/  include_everything; int /*<<< orphan*/  lockWaitTimeout; int /*<<< orphan*/  no_subscriptions; int /*<<< orphan*/  no_security_labels; int /*<<< orphan*/  no_publications; int /*<<< orphan*/  no_comments; int /*<<< orphan*/  dump_inserts; int /*<<< orphan*/  disable_dollar_quoting; int /*<<< orphan*/  use_setsessauth; int /*<<< orphan*/  disable_triggers; int /*<<< orphan*/  outputNoTablespaces; int /*<<< orphan*/  outputNoOwner; int /*<<< orphan*/  outputCreateDB; int /*<<< orphan*/  outputSuperuser; int /*<<< orphan*/  aclsSkip; int /*<<< orphan*/  dumpSections; int /*<<< orphan*/  column_inserts; int /*<<< orphan*/  if_exists; int /*<<< orphan*/  schemaOnly; int /*<<< orphan*/  dataOnly; int /*<<< orphan*/  outputClean; } ;
struct TYPE_6__ {int /*<<< orphan*/  sequence_data; int /*<<< orphan*/  enable_row_security; int /*<<< orphan*/  include_everything; int /*<<< orphan*/  lockWaitTimeout; int /*<<< orphan*/  no_subscriptions; int /*<<< orphan*/  no_security_labels; int /*<<< orphan*/  no_publications; int /*<<< orphan*/  no_comments; int /*<<< orphan*/  dump_inserts; int /*<<< orphan*/  disable_dollar_quoting; int /*<<< orphan*/  use_setsessauth; int /*<<< orphan*/  disable_triggers; int /*<<< orphan*/  noTablespace; int /*<<< orphan*/  noOwner; int /*<<< orphan*/  createDB; int /*<<< orphan*/  superuser; int /*<<< orphan*/  aclsSkip; int /*<<< orphan*/  dumpSections; int /*<<< orphan*/  column_inserts; int /*<<< orphan*/  if_exists; int /*<<< orphan*/  schemaOnly; int /*<<< orphan*/  dataOnly; int /*<<< orphan*/  dropSchema; } ;
typedef  TYPE_1__ RestoreOptions ;
typedef  TYPE_2__ DumpOptions ;

/* Variables and functions */
 TYPE_2__* NewDumpOptions () ; 

DumpOptions *
dumpOptionsFromRestoreOptions(RestoreOptions *ropt)
{
	DumpOptions *dopt = NewDumpOptions();

	/* this is the inverse of what's at the end of pg_dump.c's main() */
	dopt->outputClean = ropt->dropSchema;
	dopt->dataOnly = ropt->dataOnly;
	dopt->schemaOnly = ropt->schemaOnly;
	dopt->if_exists = ropt->if_exists;
	dopt->column_inserts = ropt->column_inserts;
	dopt->dumpSections = ropt->dumpSections;
	dopt->aclsSkip = ropt->aclsSkip;
	dopt->outputSuperuser = ropt->superuser;
	dopt->outputCreateDB = ropt->createDB;
	dopt->outputNoOwner = ropt->noOwner;
	dopt->outputNoTablespaces = ropt->noTablespace;
	dopt->disable_triggers = ropt->disable_triggers;
	dopt->use_setsessauth = ropt->use_setsessauth;
	dopt->disable_dollar_quoting = ropt->disable_dollar_quoting;
	dopt->dump_inserts = ropt->dump_inserts;
	dopt->no_comments = ropt->no_comments;
	dopt->no_publications = ropt->no_publications;
	dopt->no_security_labels = ropt->no_security_labels;
	dopt->no_subscriptions = ropt->no_subscriptions;
	dopt->lockWaitTimeout = ropt->lockWaitTimeout;
	dopt->include_everything = ropt->include_everything;
	dopt->enable_row_security = ropt->enable_row_security;
	dopt->sequence_data = ropt->sequence_data;

	return dopt;
}