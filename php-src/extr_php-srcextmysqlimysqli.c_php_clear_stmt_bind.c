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
struct TYPE_4__ {struct TYPE_4__* query; int /*<<< orphan*/  link_handle; int /*<<< orphan*/  result; int /*<<< orphan*/  param; scalar_t__ stmt; } ;
typedef  TYPE_1__ MY_STMT ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  FETCH_RESULT ; 
 int /*<<< orphan*/  FETCH_SIMPLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 scalar_t__ mysqli_stmt_close (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_free_stmt_bind_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

void php_clear_stmt_bind(MY_STMT *stmt)
{
	if (stmt->stmt) {
		if (mysqli_stmt_close(stmt->stmt, TRUE)) {
			php_error_docref(NULL, E_WARNING, "Error occurred while closing statement");
			return;
		}
	}

	/*
	  mysqlnd keeps track of the binding and has freed its
	  structures in stmt_close() above
	*/
#ifndef MYSQLI_USE_MYSQLND
	/* Clean param bind */
	php_free_stmt_bind_buffer(stmt->param, FETCH_SIMPLE);
	/* Clean output bind */
	php_free_stmt_bind_buffer(stmt->result, FETCH_RESULT);

	if (!Z_ISUNDEF(stmt->link_handle)) {
		zval_ptr_dtor(&stmt->link_handle);
	}
#endif
	if (stmt->query) {
		efree(stmt->query);
	}
	efree(stmt);
}