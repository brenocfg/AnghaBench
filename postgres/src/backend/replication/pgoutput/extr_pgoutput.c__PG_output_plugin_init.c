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
struct TYPE_4__ {int /*<<< orphan*/  shutdown_cb; int /*<<< orphan*/  filter_by_origin_cb; int /*<<< orphan*/  commit_cb; int /*<<< orphan*/  truncate_cb; int /*<<< orphan*/  change_cb; int /*<<< orphan*/  begin_cb; int /*<<< orphan*/  startup_cb; } ;
typedef  TYPE_1__ OutputPluginCallbacks ;

/* Variables and functions */
 int /*<<< orphan*/  AssertVariableIsOfType (void (*) (TYPE_1__*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogicalOutputPluginInit ; 
 int /*<<< orphan*/  pgoutput_begin_txn ; 
 int /*<<< orphan*/  pgoutput_change ; 
 int /*<<< orphan*/  pgoutput_commit_txn ; 
 int /*<<< orphan*/  pgoutput_origin_filter ; 
 int /*<<< orphan*/  pgoutput_shutdown ; 
 int /*<<< orphan*/  pgoutput_startup ; 
 int /*<<< orphan*/  pgoutput_truncate ; 

void
_PG_output_plugin_init(OutputPluginCallbacks *cb)
{
	AssertVariableIsOfType(&_PG_output_plugin_init, LogicalOutputPluginInit);

	cb->startup_cb = pgoutput_startup;
	cb->begin_cb = pgoutput_begin_txn;
	cb->change_cb = pgoutput_change;
	cb->truncate_cb = pgoutput_truncate;
	cb->commit_cb = pgoutput_commit_txn;
	cb->filter_by_origin_cb = pgoutput_origin_filter;
	cb->shutdown_cb = pgoutput_shutdown;
}