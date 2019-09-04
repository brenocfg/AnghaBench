#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pdo_sqlite_func {int /*<<< orphan*/  fini; int /*<<< orphan*/  afini; } ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  do_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_sqlite3_func_final_callback(sqlite3_context *context)
{
	struct pdo_sqlite_func *func = (struct pdo_sqlite_func*)sqlite3_user_data(context);

	do_callback(&func->afini, &func->fini, 0, NULL, context, 1);
}