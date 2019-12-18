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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  SharedInvalidationMessage ;
typedef  int /*<<< orphan*/  ReorderBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  AbortCurrentTransaction () ; 
 int /*<<< orphan*/  BeginInternalSubTransaction (char*) ; 
 int IsTransactionOrTransactionBlock () ; 
 int /*<<< orphan*/  LocalExecuteInvalidationMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RollbackAndReleaseCurrentSubTransaction () ; 

void
ReorderBufferImmediateInvalidation(ReorderBuffer *rb, uint32 ninvalidations,
								   SharedInvalidationMessage *invalidations)
{
	bool		use_subtxn = IsTransactionOrTransactionBlock();
	int			i;

	if (use_subtxn)
		BeginInternalSubTransaction("replay");

	/*
	 * Force invalidations to happen outside of a valid transaction - that way
	 * entries will just be marked as invalid without accessing the catalog.
	 * That's advantageous because we don't need to setup the full state
	 * necessary for catalog access.
	 */
	if (use_subtxn)
		AbortCurrentTransaction();

	for (i = 0; i < ninvalidations; i++)
		LocalExecuteInvalidationMessage(&invalidations[i]);

	if (use_subtxn)
		RollbackAndReleaseCurrentSubTransaction();
}