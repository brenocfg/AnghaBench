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
typedef  int WaitEventIPC ;

/* Variables and functions */
#define  WAIT_EVENT_BGWORKER_SHUTDOWN 164 
#define  WAIT_EVENT_BGWORKER_STARTUP 163 
#define  WAIT_EVENT_BTREE_PAGE 162 
#define  WAIT_EVENT_CHECKPOINT_DONE 161 
#define  WAIT_EVENT_CHECKPOINT_START 160 
#define  WAIT_EVENT_CLOG_GROUP_UPDATE 159 
#define  WAIT_EVENT_EXECUTE_GATHER 158 
#define  WAIT_EVENT_HASH_BATCH_ALLOCATING 157 
#define  WAIT_EVENT_HASH_BATCH_ELECTING 156 
#define  WAIT_EVENT_HASH_BATCH_LOADING 155 
#define  WAIT_EVENT_HASH_BUILD_ALLOCATING 154 
#define  WAIT_EVENT_HASH_BUILD_ELECTING 153 
#define  WAIT_EVENT_HASH_BUILD_HASHING_INNER 152 
#define  WAIT_EVENT_HASH_BUILD_HASHING_OUTER 151 
#define  WAIT_EVENT_HASH_GROW_BATCHES_ALLOCATING 150 
#define  WAIT_EVENT_HASH_GROW_BATCHES_DECIDING 149 
#define  WAIT_EVENT_HASH_GROW_BATCHES_ELECTING 148 
#define  WAIT_EVENT_HASH_GROW_BATCHES_FINISHING 147 
#define  WAIT_EVENT_HASH_GROW_BATCHES_REPARTITIONING 146 
#define  WAIT_EVENT_HASH_GROW_BUCKETS_ALLOCATING 145 
#define  WAIT_EVENT_HASH_GROW_BUCKETS_ELECTING 144 
#define  WAIT_EVENT_HASH_GROW_BUCKETS_REINSERTING 143 
#define  WAIT_EVENT_LOGICAL_SYNC_DATA 142 
#define  WAIT_EVENT_LOGICAL_SYNC_STATE_CHANGE 141 
#define  WAIT_EVENT_MQ_INTERNAL 140 
#define  WAIT_EVENT_MQ_PUT_MESSAGE 139 
#define  WAIT_EVENT_MQ_RECEIVE 138 
#define  WAIT_EVENT_MQ_SEND 137 
#define  WAIT_EVENT_PARALLEL_BITMAP_SCAN 136 
#define  WAIT_EVENT_PARALLEL_CREATE_INDEX_SCAN 135 
#define  WAIT_EVENT_PARALLEL_FINISH 134 
#define  WAIT_EVENT_PROCARRAY_GROUP_UPDATE 133 
#define  WAIT_EVENT_PROMOTE 132 
#define  WAIT_EVENT_REPLICATION_ORIGIN_DROP 131 
#define  WAIT_EVENT_REPLICATION_SLOT_DROP 130 
#define  WAIT_EVENT_SAFE_SNAPSHOT 129 
#define  WAIT_EVENT_SYNC_REP 128 

__attribute__((used)) static const char *
pgstat_get_wait_ipc(WaitEventIPC w)
{
	const char *event_name = "unknown wait event";

	switch (w)
	{
		case WAIT_EVENT_BGWORKER_SHUTDOWN:
			event_name = "BgWorkerShutdown";
			break;
		case WAIT_EVENT_BGWORKER_STARTUP:
			event_name = "BgWorkerStartup";
			break;
		case WAIT_EVENT_BTREE_PAGE:
			event_name = "BtreePage";
			break;
		case WAIT_EVENT_CHECKPOINT_DONE:
			event_name = "CheckpointDone";
			break;
		case WAIT_EVENT_CHECKPOINT_START:
			event_name = "CheckpointStart";
			break;
		case WAIT_EVENT_CLOG_GROUP_UPDATE:
			event_name = "ClogGroupUpdate";
			break;
		case WAIT_EVENT_EXECUTE_GATHER:
			event_name = "ExecuteGather";
			break;
		case WAIT_EVENT_HASH_BATCH_ALLOCATING:
			event_name = "Hash/Batch/Allocating";
			break;
		case WAIT_EVENT_HASH_BATCH_ELECTING:
			event_name = "Hash/Batch/Electing";
			break;
		case WAIT_EVENT_HASH_BATCH_LOADING:
			event_name = "Hash/Batch/Loading";
			break;
		case WAIT_EVENT_HASH_BUILD_ALLOCATING:
			event_name = "Hash/Build/Allocating";
			break;
		case WAIT_EVENT_HASH_BUILD_ELECTING:
			event_name = "Hash/Build/Electing";
			break;
		case WAIT_EVENT_HASH_BUILD_HASHING_INNER:
			event_name = "Hash/Build/HashingInner";
			break;
		case WAIT_EVENT_HASH_BUILD_HASHING_OUTER:
			event_name = "Hash/Build/HashingOuter";
			break;
		case WAIT_EVENT_HASH_GROW_BATCHES_ALLOCATING:
			event_name = "Hash/GrowBatches/Allocating";
			break;
		case WAIT_EVENT_HASH_GROW_BATCHES_DECIDING:
			event_name = "Hash/GrowBatches/Deciding";
			break;
		case WAIT_EVENT_HASH_GROW_BATCHES_ELECTING:
			event_name = "Hash/GrowBatches/Electing";
			break;
		case WAIT_EVENT_HASH_GROW_BATCHES_FINISHING:
			event_name = "Hash/GrowBatches/Finishing";
			break;
		case WAIT_EVENT_HASH_GROW_BATCHES_REPARTITIONING:
			event_name = "Hash/GrowBatches/Repartitioning";
			break;
		case WAIT_EVENT_HASH_GROW_BUCKETS_ALLOCATING:
			event_name = "Hash/GrowBuckets/Allocating";
			break;
		case WAIT_EVENT_HASH_GROW_BUCKETS_ELECTING:
			event_name = "Hash/GrowBuckets/Electing";
			break;
		case WAIT_EVENT_HASH_GROW_BUCKETS_REINSERTING:
			event_name = "Hash/GrowBuckets/Reinserting";
			break;
		case WAIT_EVENT_LOGICAL_SYNC_DATA:
			event_name = "LogicalSyncData";
			break;
		case WAIT_EVENT_LOGICAL_SYNC_STATE_CHANGE:
			event_name = "LogicalSyncStateChange";
			break;
		case WAIT_EVENT_MQ_INTERNAL:
			event_name = "MessageQueueInternal";
			break;
		case WAIT_EVENT_MQ_PUT_MESSAGE:
			event_name = "MessageQueuePutMessage";
			break;
		case WAIT_EVENT_MQ_RECEIVE:
			event_name = "MessageQueueReceive";
			break;
		case WAIT_EVENT_MQ_SEND:
			event_name = "MessageQueueSend";
			break;
		case WAIT_EVENT_PARALLEL_BITMAP_SCAN:
			event_name = "ParallelBitmapScan";
			break;
		case WAIT_EVENT_PARALLEL_CREATE_INDEX_SCAN:
			event_name = "ParallelCreateIndexScan";
			break;
		case WAIT_EVENT_PARALLEL_FINISH:
			event_name = "ParallelFinish";
			break;
		case WAIT_EVENT_PROCARRAY_GROUP_UPDATE:
			event_name = "ProcArrayGroupUpdate";
			break;
		case WAIT_EVENT_PROMOTE:
			event_name = "Promote";
			break;
		case WAIT_EVENT_REPLICATION_ORIGIN_DROP:
			event_name = "ReplicationOriginDrop";
			break;
		case WAIT_EVENT_REPLICATION_SLOT_DROP:
			event_name = "ReplicationSlotDrop";
			break;
		case WAIT_EVENT_SAFE_SNAPSHOT:
			event_name = "SafeSnapshot";
			break;
		case WAIT_EVENT_SYNC_REP:
			event_name = "SyncRep";
			break;
			/* no default case, so that compiler will warn */
	}

	return event_name;
}