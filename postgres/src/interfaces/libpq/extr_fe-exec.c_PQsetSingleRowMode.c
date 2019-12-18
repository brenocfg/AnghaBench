#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ asyncStatus; scalar_t__ queryclass; int singleRowMode; scalar_t__ result; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ PGASYNC_BUSY ; 
 scalar_t__ PGQUERY_EXTENDED ; 
 scalar_t__ PGQUERY_SIMPLE ; 

int
PQsetSingleRowMode(PGconn *conn)
{
	/*
	 * Only allow setting the flag when we have launched a query and not yet
	 * received any results.
	 */
	if (!conn)
		return 0;
	if (conn->asyncStatus != PGASYNC_BUSY)
		return 0;
	if (conn->queryclass != PGQUERY_SIMPLE &&
		conn->queryclass != PGQUERY_EXTENDED)
		return 0;
	if (conn->result)
		return 0;

	/* OK, set flag */
	conn->singleRowMode = true;
	return 1;
}