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
struct TYPE_4__ {scalar_t__ status; int nonblocking; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ CONNECTION_BAD ; 
 scalar_t__ pqFlush (TYPE_1__*) ; 

int
PQsetnonblocking(PGconn *conn, int arg)
{
	bool		barg;

	if (!conn || conn->status == CONNECTION_BAD)
		return -1;

	barg = (arg ? true : false);

	/* early out if the socket is already in the state requested */
	if (barg == conn->nonblocking)
		return 0;

	/*
	 * to guarantee constancy for flushing/query/result-polling behavior we
	 * need to flush the send queue at this point in order to guarantee proper
	 * behavior. this is ok because either they are making a transition _from_
	 * or _to_ blocking mode, either way we can block them.
	 */
	/* if we are going from blocking to non-blocking flush here */
	if (pqFlush(conn))
		return -1;

	conn->nonblocking = barg;

	return 0;
}