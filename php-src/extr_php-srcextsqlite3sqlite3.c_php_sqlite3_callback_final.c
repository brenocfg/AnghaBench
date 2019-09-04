#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_3__ {int /*<<< orphan*/  fini; int /*<<< orphan*/  afini; } ;
typedef  TYPE_1__ php_sqlite3_func ;
struct TYPE_4__ {scalar_t__ row_count; } ;
typedef  TYPE_2__ php_sqlite3_agg_context ;

/* Variables and functions */
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_do_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_sqlite3_callback_final(sqlite3_context *context) /* {{{ */
{
	php_sqlite3_func *func = (php_sqlite3_func *)sqlite3_user_data(context);
	php_sqlite3_agg_context *agg_context = (php_sqlite3_agg_context *)sqlite3_aggregate_context(context, sizeof(php_sqlite3_agg_context));

	agg_context->row_count = 0;

	sqlite3_do_callback(&func->afini, &func->fini, 0, NULL, context, 1);
}