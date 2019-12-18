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
 scalar_t__ ActiveSnapshotSet () ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TRANSACTION_TERMINATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HoldPinnedPortals () ; 
 scalar_t__ IsSubTransaction () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  RestoreTransactionCharacteristics () ; 
 int /*<<< orphan*/  SaveTransactionCharacteristics () ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 TYPE_1__* _SPI_current ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
_SPI_commit(bool chain)
{
	MemoryContext oldcontext = CurrentMemoryContext;

	if (_SPI_current->atomic)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TRANSACTION_TERMINATION),
				 errmsg("invalid transaction termination")));

	/*
	 * This restriction is required by PLs implemented on top of SPI.  They
	 * use subtransactions to establish exception blocks that are supposed to
	 * be rolled back together if there is an error.  Terminating the
	 * top-level transaction in such a block violates that idea.  A future PL
	 * implementation might have different ideas about this, in which case
	 * this restriction would have to be refined or the check possibly be
	 * moved out of SPI into the PLs.
	 */
	if (IsSubTransaction())
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TRANSACTION_TERMINATION),
				 errmsg("cannot commit while a subtransaction is active")));

	/*
	 * Hold any pinned portals that any PLs might be using.  We have to do
	 * this before changing transaction state, since this will run
	 * user-defined code that might throw an error.
	 */
	HoldPinnedPortals();

	/* Start the actual commit */
	_SPI_current->internal_xact = true;

	/*
	 * Before committing, pop all active snapshots to avoid error about
	 * "snapshot %p still active".
	 */
	while (ActiveSnapshotSet())
		PopActiveSnapshot();

	if (chain)
		SaveTransactionCharacteristics();

	CommitTransactionCommand();

	if (chain)
	{
		StartTransactionCommand();
		RestoreTransactionCharacteristics();
	}

	MemoryContextSwitchTo(oldcontext);

	_SPI_current->internal_xact = false;
}