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
struct TYPE_2__ {int internal_xact; scalar_t__ atomic; } ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  AbortCurrentTransaction () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TRANSACTION_TERMINATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HoldPinnedPortals () ; 
 scalar_t__ IsSubTransaction () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RestoreTransactionCharacteristics () ; 
 int /*<<< orphan*/  SaveTransactionCharacteristics () ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 TYPE_1__* _SPI_current ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
_SPI_rollback(bool chain)
{
	MemoryContext oldcontext = CurrentMemoryContext;

	if (_SPI_current->atomic)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TRANSACTION_TERMINATION),
				 errmsg("invalid transaction termination")));

	/* see under SPI_commit() */
	if (IsSubTransaction())
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TRANSACTION_TERMINATION),
				 errmsg("cannot roll back while a subtransaction is active")));

	/*
	 * Hold any pinned portals that any PLs might be using.  We have to do
	 * this before changing transaction state, since this will run
	 * user-defined code that might throw an error, and in any case couldn't
	 * be run in an already-aborted transaction.
	 */
	HoldPinnedPortals();

	/* Start the actual rollback */
	_SPI_current->internal_xact = true;

	if (chain)
		SaveTransactionCharacteristics();

	AbortCurrentTransaction();

	if (chain)
	{
		StartTransactionCommand();
		RestoreTransactionCharacteristics();
	}

	MemoryContextSwitchTo(oldcontext);

	_SPI_current->internal_xact = false;
}