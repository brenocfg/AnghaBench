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
 int /*<<< orphan*/  InvalidSerializableXact ; 
 int /*<<< orphan*/ * LocalPredicateLockHash ; 
 int /*<<< orphan*/  MySerializableXact ; 
 int MyXactDidWrite ; 
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ReleasePredicateLocksLocal(void)
{
	MySerializableXact = InvalidSerializableXact;
	MyXactDidWrite = false;

	/* Delete per-transaction lock table */
	if (LocalPredicateLockHash != NULL)
	{
		hash_destroy(LocalPredicateLockHash);
		LocalPredicateLockHash = NULL;
	}
}