#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_stmt_t ;
struct TYPE_8__ {scalar_t__ cursor_open; scalar_t__* name; int /*<<< orphan*/  stmt; TYPE_1__* H; } ;
typedef  TYPE_3__ pdo_firebird_stmt ;
struct TYPE_6__ {int /*<<< orphan*/  isc_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSQL_close ; 
 int /*<<< orphan*/  RECORD_ERROR (TYPE_2__*) ; 
 scalar_t__ isc_dsql_free_statement (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int firebird_stmt_cursor_closer(pdo_stmt_t *stmt) /* {{{ */
{
	pdo_firebird_stmt *S = (pdo_firebird_stmt*)stmt->driver_data;

	/* close the statement handle */
	if ((*S->name || S->cursor_open) && isc_dsql_free_statement(S->H->isc_status, &S->stmt, DSQL_close)) {
		RECORD_ERROR(stmt);
		return 0;
	}
	*S->name = 0;
	S->cursor_open = 0;
	return 1;
}