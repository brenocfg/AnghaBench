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
struct TYPE_4__ {scalar_t__ asyncStatus; scalar_t__ write_failed; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ PGASYNC_BUSY ; 
 int /*<<< orphan*/  parseInput (TYPE_1__*) ; 

int
PQisBusy(PGconn *conn)
{
	if (!conn)
		return false;

	/* Parse any available data, if our state permits. */
	parseInput(conn);

	/*
	 * PQgetResult will return immediately in all states except BUSY, or if we
	 * had a write failure.
	 */
	return conn->asyncStatus == PGASYNC_BUSY || conn->write_failed;
}