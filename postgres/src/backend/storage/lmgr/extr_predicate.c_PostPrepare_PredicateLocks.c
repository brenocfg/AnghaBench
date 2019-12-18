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
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* InvalidSerializableXact ; 
 int /*<<< orphan*/ * LocalPredicateLockHash ; 
 TYPE_1__* MySerializableXact ; 
 int MyXactDidWrite ; 
 int /*<<< orphan*/  SxactIsPrepared (TYPE_1__*) ; 
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 

void
PostPrepare_PredicateLocks(TransactionId xid)
{
	if (MySerializableXact == InvalidSerializableXact)
		return;

	Assert(SxactIsPrepared(MySerializableXact));

	MySerializableXact->pid = 0;

	hash_destroy(LocalPredicateLockHash);
	LocalPredicateLockHash = NULL;

	MySerializableXact = InvalidSerializableXact;
	MyXactDidWrite = false;
}