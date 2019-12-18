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
typedef  TYPE_1__* TransactionState ;
struct TYPE_3__ {scalar_t__ blockState; struct TYPE_3__* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__* CurrentTransactionState ; 
 int EndTransactionBlock (int) ; 
 int /*<<< orphan*/  MemoryContextStrdup (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ TBLOCK_END ; 
 scalar_t__ TBLOCK_IMPLICIT_INPROGRESS ; 
 scalar_t__ TBLOCK_PREPARE ; 
 scalar_t__ TBLOCK_STARTED ; 
 int /*<<< orphan*/  TopTransactionContext ; 
 int /*<<< orphan*/  prepareGID ; 

bool
PrepareTransactionBlock(const char *gid)
{
	TransactionState s;
	bool		result;

	/* Set up to commit the current transaction */
	result = EndTransactionBlock(false);

	/* If successful, change outer tblock state to PREPARE */
	if (result)
	{
		s = CurrentTransactionState;

		while (s->parent != NULL)
			s = s->parent;

		if (s->blockState == TBLOCK_END)
		{
			/* Save GID where PrepareTransaction can find it again */
			prepareGID = MemoryContextStrdup(TopTransactionContext, gid);

			s->blockState = TBLOCK_PREPARE;
		}
		else
		{
			/*
			 * ignore case where we are not in a transaction;
			 * EndTransactionBlock already issued a warning.
			 */
			Assert(s->blockState == TBLOCK_STARTED ||
				   s->blockState == TBLOCK_IMPLICIT_INPROGRESS);
			/* Don't send back a PREPARE result tag... */
			result = false;
		}
	}

	return result;
}