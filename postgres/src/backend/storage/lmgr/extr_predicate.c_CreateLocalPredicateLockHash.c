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
typedef  int /*<<< orphan*/  hash_ctl ;
struct TYPE_4__ {int keysize; int entrysize; } ;
typedef  int /*<<< orphan*/  PREDICATELOCKTARGETTAG ;
typedef  int /*<<< orphan*/  LOCALPREDICATELOCK ;
typedef  TYPE_1__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/ * LocalPredicateLockHash ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * hash_create (char*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  max_predicate_locks_per_xact ; 

__attribute__((used)) static void
CreateLocalPredicateLockHash(void)
{
	HASHCTL		hash_ctl;

	/* Initialize the backend-local hash table of parent locks */
	Assert(LocalPredicateLockHash == NULL);
	MemSet(&hash_ctl, 0, sizeof(hash_ctl));
	hash_ctl.keysize = sizeof(PREDICATELOCKTARGETTAG);
	hash_ctl.entrysize = sizeof(LOCALPREDICATELOCK);
	LocalPredicateLockHash = hash_create("Local predicate lock",
										 max_predicate_locks_per_xact,
										 &hash_ctl,
										 HASH_ELEM | HASH_BLOBS);
}