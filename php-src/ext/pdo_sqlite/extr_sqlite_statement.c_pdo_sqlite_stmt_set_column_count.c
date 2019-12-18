#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int column_count; TYPE_3__* columns; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_5__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pdo_sqlite_stmt_set_column_count(pdo_stmt_t *stmt, int new_count)
{
	/* Columns not yet "described" */
	if (!stmt->columns) {
		stmt->column_count = new_count;

		return;
	}

	/*
	 * The column count has not changed : no need to reload columns description 
	 * Note: Do not handle attribute name change, without column count change
	 */
	if (new_count == stmt->column_count) {
		return;
	}

	/* Free previous columns to force reload description */
	int i;

	for (i = 0; i < stmt->column_count; i++) {
		if (stmt->columns[i].name) {
			zend_string_release(stmt->columns[i].name);
			stmt->columns[i].name = NULL;
		}
	}

	efree(stmt->columns);
	stmt->columns = NULL;
	stmt->column_count = new_count;
}