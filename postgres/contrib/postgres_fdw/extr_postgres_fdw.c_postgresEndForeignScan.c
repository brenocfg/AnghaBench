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
struct TYPE_5__ {scalar_t__ fdw_state; } ;
struct TYPE_4__ {int /*<<< orphan*/ * conn; int /*<<< orphan*/  cursor_number; scalar_t__ cursor_exists; } ;
typedef  TYPE_1__ PgFdwScanState ;
typedef  TYPE_2__ ForeignScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
postgresEndForeignScan(ForeignScanState *node)
{
	PgFdwScanState *fsstate = (PgFdwScanState *) node->fdw_state;

	/* if fsstate is NULL, we are in EXPLAIN; nothing to do */
	if (fsstate == NULL)
		return;

	/* Close the cursor if open, to prevent accumulation of cursors */
	if (fsstate->cursor_exists)
		close_cursor(fsstate->conn, fsstate->cursor_number);

	/* Release remote connection */
	ReleaseConnection(fsstate->conn);
	fsstate->conn = NULL;

	/* MemoryContexts will be deleted automatically. */
}