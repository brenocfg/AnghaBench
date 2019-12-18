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
struct TYPE_4__ {int /*<<< orphan*/  message_cb; int /*<<< orphan*/  shutdown_cb; int /*<<< orphan*/  filter_by_origin_cb; int /*<<< orphan*/  commit_cb; int /*<<< orphan*/  truncate_cb; int /*<<< orphan*/  change_cb; int /*<<< orphan*/  begin_cb; int /*<<< orphan*/  startup_cb; } ;
typedef  TYPE_1__ OutputPluginCallbacks ;

/* Variables and functions */
 int /*<<< orphan*/  AssertVariableIsOfType (void (*) (TYPE_1__*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogicalOutputPluginInit ; 
 int /*<<< orphan*/  pg_decode_begin_txn ; 
 int /*<<< orphan*/  pg_decode_change ; 
 int /*<<< orphan*/  pg_decode_commit_txn ; 
 int /*<<< orphan*/  pg_decode_filter ; 
 int /*<<< orphan*/  pg_decode_message ; 
 int /*<<< orphan*/  pg_decode_shutdown ; 
 int /*<<< orphan*/  pg_decode_startup ; 
 int /*<<< orphan*/  pg_decode_truncate ; 

void
_PG_output_plugin_init(OutputPluginCallbacks *cb)
{
	AssertVariableIsOfType(&_PG_output_plugin_init, LogicalOutputPluginInit);

	cb->startup_cb = pg_decode_startup;
	cb->begin_cb = pg_decode_begin_txn;
	cb->change_cb = pg_decode_change;
	cb->truncate_cb = pg_decode_truncate;
	cb->commit_cb = pg_decode_commit_txn;
	cb->filter_by_origin_cb = pg_decode_filter;
	cb->shutdown_cb = pg_decode_shutdown;
	cb->message_cb = pg_decode_message;
}