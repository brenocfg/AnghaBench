#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_2__ {int /*<<< orphan*/  func; int /*<<< orphan*/  afunc; } ;
typedef  TYPE_1__ php_sqlite3_func ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_do_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_sqlite3_callback_func(sqlite3_context *context, int argc, sqlite3_value **argv) /* {{{ */
{
	php_sqlite3_func *func = (php_sqlite3_func *)sqlite3_user_data(context);

	sqlite3_do_callback(&func->afunc, &func->func, argc, argv, context, 0);
}