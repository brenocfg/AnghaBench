#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ pqFlush (int /*<<< orphan*/ *) ; 
 scalar_t__ pqIsnonblocking (int /*<<< orphan*/ *) ; 
 scalar_t__ pqReadData (int /*<<< orphan*/ *) ; 

int
PQconsumeInput(PGconn *conn)
{
	if (!conn)
		return 0;

	/*
	 * for non-blocking connections try to flush the send-queue, otherwise we
	 * may never get a response for something that may not have already been
	 * sent because it's in our write buffer!
	 */
	if (pqIsnonblocking(conn))
	{
		if (pqFlush(conn) < 0)
			return 0;
	}

	/*
	 * Load more data, if available. We do this no matter what state we are
	 * in, since we are probably getting called because the application wants
	 * to get rid of a read-select condition. Note that we will NOT block
	 * waiting for more input.
	 */
	if (pqReadData(conn) < 0)
		return 0;

	/* Parsing of the data waits till later. */
	return 1;
}