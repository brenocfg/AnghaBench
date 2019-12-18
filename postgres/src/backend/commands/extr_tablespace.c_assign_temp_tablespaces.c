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
struct TYPE_2__ {int /*<<< orphan*/  numSpcs; int /*<<< orphan*/ * tblSpcs; } ;
typedef  TYPE_1__ temp_tablespaces_extra ;

/* Variables and functions */
 int /*<<< orphan*/  SetTempTablespaces (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
assign_temp_tablespaces(const char *newval, void *extra)
{
	temp_tablespaces_extra *myextra = (temp_tablespaces_extra *) extra;

	/*
	 * If check_temp_tablespaces was executed inside a transaction, then pass
	 * the list it made to fd.c.  Otherwise, clear fd.c's list; we must be
	 * still outside a transaction, or else restoring during transaction exit,
	 * and in either case we can just let the next PrepareTempTablespaces call
	 * make things sane.
	 */
	if (myextra)
		SetTempTablespaces(myextra->tblSpcs, myextra->numSpcs);
	else
		SetTempTablespaces(NULL, 0);
}