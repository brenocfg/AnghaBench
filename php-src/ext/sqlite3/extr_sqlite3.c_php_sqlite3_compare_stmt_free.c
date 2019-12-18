#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_5__ {TYPE_1__* stmt_obj; } ;
typedef  TYPE_2__ php_sqlite3_free_list ;
struct TYPE_4__ {int /*<<< orphan*/ * stmt; scalar_t__ initialised; } ;

/* Variables and functions */

__attribute__((used)) static int php_sqlite3_compare_stmt_free( php_sqlite3_free_list **free_list, sqlite3_stmt *statement ) /* {{{ */
{
	return ((*free_list)->stmt_obj->initialised && statement == (*free_list)->stmt_obj->stmt);
}