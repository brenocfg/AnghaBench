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
struct TYPE_2__ {void* ckpt_sync_end_t; void* ckpt_sync_t; void* ckpt_write_t; } ;

/* Variables and functions */
 int /*<<< orphan*/  BufferSync (int) ; 
 TYPE_1__ CheckpointStats ; 
 void* GetCurrentTimestamp () ; 
 int /*<<< orphan*/  ProcessSyncRequests () ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_BUFFER_CHECKPOINT_DONE () ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_BUFFER_CHECKPOINT_START (int) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_BUFFER_CHECKPOINT_SYNC_START () ; 

void
CheckPointBuffers(int flags)
{
	TRACE_POSTGRESQL_BUFFER_CHECKPOINT_START(flags);
	CheckpointStats.ckpt_write_t = GetCurrentTimestamp();
	BufferSync(flags);
	CheckpointStats.ckpt_sync_t = GetCurrentTimestamp();
	TRACE_POSTGRESQL_BUFFER_CHECKPOINT_SYNC_START();
	ProcessSyncRequests();
	CheckpointStats.ckpt_sync_end_t = GetCurrentTimestamp();
	TRACE_POSTGRESQL_BUFFER_CHECKPOINT_DONE();
}