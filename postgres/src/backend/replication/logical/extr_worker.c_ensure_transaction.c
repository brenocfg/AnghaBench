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
 scalar_t__ ApplyMessageContext ; 
 scalar_t__ CurrentMemoryContext ; 
 scalar_t__ IsTransactionState () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (scalar_t__) ; 
 int /*<<< orphan*/  SetCurrentStatementStartTimestamp () ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  maybe_reread_subscription () ; 

__attribute__((used)) static bool
ensure_transaction(void)
{
	if (IsTransactionState())
	{
		SetCurrentStatementStartTimestamp();

		if (CurrentMemoryContext != ApplyMessageContext)
			MemoryContextSwitchTo(ApplyMessageContext);

		return false;
	}

	SetCurrentStatementStartTimestamp();
	StartTransactionCommand();

	maybe_reread_subscription();

	MemoryContextSwitchTo(ApplyMessageContext);
	return true;
}