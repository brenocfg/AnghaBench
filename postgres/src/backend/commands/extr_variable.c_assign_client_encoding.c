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

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_TRANSACTION_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InitializingParallelWorker ; 
 scalar_t__ IsParallelWorker () ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ SetClientEncoding (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

void
assign_client_encoding(const char *newval, void *extra)
{
	int			encoding = *((int *) extra);

	/*
	 * Parallel workers send data to the leader, not the client.  They always
	 * send data using the database encoding.
	 */
	if (IsParallelWorker())
	{
		/*
		 * During parallel worker startup, we want to accept the leader's
		 * client_encoding setting so that anyone who looks at the value in
		 * the worker sees the same value that they would see in the leader.
		 */
		if (InitializingParallelWorker)
			return;

		/*
		 * A change other than during startup, for example due to a SET clause
		 * attached to a function definition, should be rejected, as there is
		 * nothing we can do inside the worker to make it take effect.
		 */
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TRANSACTION_STATE),
				 errmsg("cannot change client_encoding during a parallel operation")));
	}

	/* We do not expect an error if PrepareClientEncoding succeeded */
	if (SetClientEncoding(encoding) < 0)
		elog(LOG, "SetClientEncoding(%d) failed", encoding);
}