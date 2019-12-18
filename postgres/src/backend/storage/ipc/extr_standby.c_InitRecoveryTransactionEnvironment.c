#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash_ctl ;
struct TYPE_6__ {int /*<<< orphan*/  localTransactionId; int /*<<< orphan*/  backendId; } ;
typedef  TYPE_1__ VirtualTransactionId ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_7__ {int keysize; int entrysize; } ;
typedef  int /*<<< orphan*/  RecoveryLockListsEntry ;
typedef  TYPE_2__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  GetNextLocalTransactionId () ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  MyBackendId ; 
 int /*<<< orphan*/  RecoveryLockLists ; 
 int /*<<< orphan*/  STANDBY_INITIALIZED ; 
 int /*<<< orphan*/  SharedInvalBackendInit (int) ; 
 int /*<<< orphan*/  VirtualXactLockTableInsert (TYPE_1__) ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  standbyState ; 

void
InitRecoveryTransactionEnvironment(void)
{
	VirtualTransactionId vxid;
	HASHCTL		hash_ctl;

	/*
	 * Initialize the hash table for tracking the list of locks held by each
	 * transaction.
	 */
	memset(&hash_ctl, 0, sizeof(hash_ctl));
	hash_ctl.keysize = sizeof(TransactionId);
	hash_ctl.entrysize = sizeof(RecoveryLockListsEntry);
	RecoveryLockLists = hash_create("RecoveryLockLists",
									64,
									&hash_ctl,
									HASH_ELEM | HASH_BLOBS);

	/*
	 * Initialize shared invalidation management for Startup process, being
	 * careful to register ourselves as a sendOnly process so we don't need to
	 * read messages, nor will we get signalled when the queue starts filling
	 * up.
	 */
	SharedInvalBackendInit(true);

	/*
	 * Lock a virtual transaction id for Startup process.
	 *
	 * We need to do GetNextLocalTransactionId() because
	 * SharedInvalBackendInit() leaves localTransactionId invalid and the lock
	 * manager doesn't like that at all.
	 *
	 * Note that we don't need to run XactLockTableInsert() because nobody
	 * needs to wait on xids. That sounds a little strange, but table locks
	 * are held by vxids and row level locks are held by xids. All queries
	 * hold AccessShareLocks so never block while we write or lock new rows.
	 */
	vxid.backendId = MyBackendId;
	vxid.localTransactionId = GetNextLocalTransactionId();
	VirtualXactLockTableInsert(vxid);

	standbyState = STANDBY_INITIALIZED;
}