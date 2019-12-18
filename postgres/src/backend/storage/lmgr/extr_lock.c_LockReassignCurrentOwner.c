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
typedef  int /*<<< orphan*/ * ResourceOwner ;
typedef  int /*<<< orphan*/  LOCALLOCK ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  LockMethodLocalHash ; 
 int /*<<< orphan*/  LockReassignOwner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ResourceOwnerGetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

void
LockReassignCurrentOwner(LOCALLOCK **locallocks, int nlocks)
{
	ResourceOwner parent = ResourceOwnerGetParent(CurrentResourceOwner);

	Assert(parent != NULL);

	if (locallocks == NULL)
	{
		HASH_SEQ_STATUS status;
		LOCALLOCK  *locallock;

		hash_seq_init(&status, LockMethodLocalHash);

		while ((locallock = (LOCALLOCK *) hash_seq_search(&status)) != NULL)
			LockReassignOwner(locallock, parent);
	}
	else
	{
		int			i;

		for (i = nlocks - 1; i >= 0; i--)
			LockReassignOwner(locallocks[i], parent);
	}
}