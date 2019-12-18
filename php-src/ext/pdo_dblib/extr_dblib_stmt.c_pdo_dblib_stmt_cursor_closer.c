#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_6__ {TYPE_3__* H; } ;
typedef  TYPE_2__ pdo_dblib_stmt ;
struct TYPE_7__ {int /*<<< orphan*/  err; int /*<<< orphan*/  link; } ;
typedef  TYPE_3__ pdo_dblib_db_handle ;

/* Variables and functions */
 int /*<<< orphan*/  dbcancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdo_dblib_err_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pdo_dblib_stmt_cursor_closer(pdo_stmt_t *stmt)
{
	pdo_dblib_stmt *S = (pdo_dblib_stmt*)stmt->driver_data;
	pdo_dblib_db_handle *H = S->H;

	/* Cancel any pending results */
	dbcancel(H->link);

	pdo_dblib_err_dtor(&H->err);

	return 1;
}