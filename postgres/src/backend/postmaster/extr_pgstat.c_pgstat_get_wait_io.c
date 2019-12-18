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
typedef  int WaitEventIO ;

/* Variables and functions */
#define  WAIT_EVENT_BUFFILE_READ 195 
#define  WAIT_EVENT_BUFFILE_WRITE 194 
#define  WAIT_EVENT_CONTROL_FILE_READ 193 
#define  WAIT_EVENT_CONTROL_FILE_SYNC 192 
#define  WAIT_EVENT_CONTROL_FILE_SYNC_UPDATE 191 
#define  WAIT_EVENT_CONTROL_FILE_WRITE 190 
#define  WAIT_EVENT_CONTROL_FILE_WRITE_UPDATE 189 
#define  WAIT_EVENT_COPY_FILE_READ 188 
#define  WAIT_EVENT_COPY_FILE_WRITE 187 
#define  WAIT_EVENT_DATA_FILE_EXTEND 186 
#define  WAIT_EVENT_DATA_FILE_FLUSH 185 
#define  WAIT_EVENT_DATA_FILE_IMMEDIATE_SYNC 184 
#define  WAIT_EVENT_DATA_FILE_PREFETCH 183 
#define  WAIT_EVENT_DATA_FILE_READ 182 
#define  WAIT_EVENT_DATA_FILE_SYNC 181 
#define  WAIT_EVENT_DATA_FILE_TRUNCATE 180 
#define  WAIT_EVENT_DATA_FILE_WRITE 179 
#define  WAIT_EVENT_DSM_FILL_ZERO_WRITE 178 
#define  WAIT_EVENT_LOCK_FILE_ADDTODATADIR_READ 177 
#define  WAIT_EVENT_LOCK_FILE_ADDTODATADIR_SYNC 176 
#define  WAIT_EVENT_LOCK_FILE_ADDTODATADIR_WRITE 175 
#define  WAIT_EVENT_LOCK_FILE_CREATE_READ 174 
#define  WAIT_EVENT_LOCK_FILE_CREATE_SYNC 173 
#define  WAIT_EVENT_LOCK_FILE_CREATE_WRITE 172 
#define  WAIT_EVENT_LOCK_FILE_RECHECKDATADIR_READ 171 
#define  WAIT_EVENT_LOGICAL_REWRITE_CHECKPOINT_SYNC 170 
#define  WAIT_EVENT_LOGICAL_REWRITE_MAPPING_SYNC 169 
#define  WAIT_EVENT_LOGICAL_REWRITE_MAPPING_WRITE 168 
#define  WAIT_EVENT_LOGICAL_REWRITE_SYNC 167 
#define  WAIT_EVENT_LOGICAL_REWRITE_TRUNCATE 166 
#define  WAIT_EVENT_LOGICAL_REWRITE_WRITE 165 
#define  WAIT_EVENT_RELATION_MAP_READ 164 
#define  WAIT_EVENT_RELATION_MAP_SYNC 163 
#define  WAIT_EVENT_RELATION_MAP_WRITE 162 
#define  WAIT_EVENT_REORDER_BUFFER_READ 161 
#define  WAIT_EVENT_REORDER_BUFFER_WRITE 160 
#define  WAIT_EVENT_REORDER_LOGICAL_MAPPING_READ 159 
#define  WAIT_EVENT_REPLICATION_SLOT_READ 158 
#define  WAIT_EVENT_REPLICATION_SLOT_RESTORE_SYNC 157 
#define  WAIT_EVENT_REPLICATION_SLOT_SYNC 156 
#define  WAIT_EVENT_REPLICATION_SLOT_WRITE 155 
#define  WAIT_EVENT_SLRU_FLUSH_SYNC 154 
#define  WAIT_EVENT_SLRU_READ 153 
#define  WAIT_EVENT_SLRU_SYNC 152 
#define  WAIT_EVENT_SLRU_WRITE 151 
#define  WAIT_EVENT_SNAPBUILD_READ 150 
#define  WAIT_EVENT_SNAPBUILD_SYNC 149 
#define  WAIT_EVENT_SNAPBUILD_WRITE 148 
#define  WAIT_EVENT_TIMELINE_HISTORY_FILE_SYNC 147 
#define  WAIT_EVENT_TIMELINE_HISTORY_FILE_WRITE 146 
#define  WAIT_EVENT_TIMELINE_HISTORY_READ 145 
#define  WAIT_EVENT_TIMELINE_HISTORY_SYNC 144 
#define  WAIT_EVENT_TIMELINE_HISTORY_WRITE 143 
#define  WAIT_EVENT_TWOPHASE_FILE_READ 142 
#define  WAIT_EVENT_TWOPHASE_FILE_SYNC 141 
#define  WAIT_EVENT_TWOPHASE_FILE_WRITE 140 
#define  WAIT_EVENT_WALSENDER_TIMELINE_HISTORY_READ 139 
#define  WAIT_EVENT_WAL_BOOTSTRAP_SYNC 138 
#define  WAIT_EVENT_WAL_BOOTSTRAP_WRITE 137 
#define  WAIT_EVENT_WAL_COPY_READ 136 
#define  WAIT_EVENT_WAL_COPY_SYNC 135 
#define  WAIT_EVENT_WAL_COPY_WRITE 134 
#define  WAIT_EVENT_WAL_INIT_SYNC 133 
#define  WAIT_EVENT_WAL_INIT_WRITE 132 
#define  WAIT_EVENT_WAL_READ 131 
#define  WAIT_EVENT_WAL_SYNC 130 
#define  WAIT_EVENT_WAL_SYNC_METHOD_ASSIGN 129 
#define  WAIT_EVENT_WAL_WRITE 128 

__attribute__((used)) static const char *
pgstat_get_wait_io(WaitEventIO w)
{
	const char *event_name = "unknown wait event";

	switch (w)
	{
		case WAIT_EVENT_BUFFILE_READ:
			event_name = "BufFileRead";
			break;
		case WAIT_EVENT_BUFFILE_WRITE:
			event_name = "BufFileWrite";
			break;
		case WAIT_EVENT_CONTROL_FILE_READ:
			event_name = "ControlFileRead";
			break;
		case WAIT_EVENT_CONTROL_FILE_SYNC:
			event_name = "ControlFileSync";
			break;
		case WAIT_EVENT_CONTROL_FILE_SYNC_UPDATE:
			event_name = "ControlFileSyncUpdate";
			break;
		case WAIT_EVENT_CONTROL_FILE_WRITE:
			event_name = "ControlFileWrite";
			break;
		case WAIT_EVENT_CONTROL_FILE_WRITE_UPDATE:
			event_name = "ControlFileWriteUpdate";
			break;
		case WAIT_EVENT_COPY_FILE_READ:
			event_name = "CopyFileRead";
			break;
		case WAIT_EVENT_COPY_FILE_WRITE:
			event_name = "CopyFileWrite";
			break;
		case WAIT_EVENT_DATA_FILE_EXTEND:
			event_name = "DataFileExtend";
			break;
		case WAIT_EVENT_DATA_FILE_FLUSH:
			event_name = "DataFileFlush";
			break;
		case WAIT_EVENT_DATA_FILE_IMMEDIATE_SYNC:
			event_name = "DataFileImmediateSync";
			break;
		case WAIT_EVENT_DATA_FILE_PREFETCH:
			event_name = "DataFilePrefetch";
			break;
		case WAIT_EVENT_DATA_FILE_READ:
			event_name = "DataFileRead";
			break;
		case WAIT_EVENT_DATA_FILE_SYNC:
			event_name = "DataFileSync";
			break;
		case WAIT_EVENT_DATA_FILE_TRUNCATE:
			event_name = "DataFileTruncate";
			break;
		case WAIT_EVENT_DATA_FILE_WRITE:
			event_name = "DataFileWrite";
			break;
		case WAIT_EVENT_DSM_FILL_ZERO_WRITE:
			event_name = "DSMFillZeroWrite";
			break;
		case WAIT_EVENT_LOCK_FILE_ADDTODATADIR_READ:
			event_name = "LockFileAddToDataDirRead";
			break;
		case WAIT_EVENT_LOCK_FILE_ADDTODATADIR_SYNC:
			event_name = "LockFileAddToDataDirSync";
			break;
		case WAIT_EVENT_LOCK_FILE_ADDTODATADIR_WRITE:
			event_name = "LockFileAddToDataDirWrite";
			break;
		case WAIT_EVENT_LOCK_FILE_CREATE_READ:
			event_name = "LockFileCreateRead";
			break;
		case WAIT_EVENT_LOCK_FILE_CREATE_SYNC:
			event_name = "LockFileCreateSync";
			break;
		case WAIT_EVENT_LOCK_FILE_CREATE_WRITE:
			event_name = "LockFileCreateWrite";
			break;
		case WAIT_EVENT_LOCK_FILE_RECHECKDATADIR_READ:
			event_name = "LockFileReCheckDataDirRead";
			break;
		case WAIT_EVENT_LOGICAL_REWRITE_CHECKPOINT_SYNC:
			event_name = "LogicalRewriteCheckpointSync";
			break;
		case WAIT_EVENT_LOGICAL_REWRITE_MAPPING_SYNC:
			event_name = "LogicalRewriteMappingSync";
			break;
		case WAIT_EVENT_LOGICAL_REWRITE_MAPPING_WRITE:
			event_name = "LogicalRewriteMappingWrite";
			break;
		case WAIT_EVENT_LOGICAL_REWRITE_SYNC:
			event_name = "LogicalRewriteSync";
			break;
		case WAIT_EVENT_LOGICAL_REWRITE_TRUNCATE:
			event_name = "LogicalRewriteTruncate";
			break;
		case WAIT_EVENT_LOGICAL_REWRITE_WRITE:
			event_name = "LogicalRewriteWrite";
			break;
		case WAIT_EVENT_RELATION_MAP_READ:
			event_name = "RelationMapRead";
			break;
		case WAIT_EVENT_RELATION_MAP_SYNC:
			event_name = "RelationMapSync";
			break;
		case WAIT_EVENT_RELATION_MAP_WRITE:
			event_name = "RelationMapWrite";
			break;
		case WAIT_EVENT_REORDER_BUFFER_READ:
			event_name = "ReorderBufferRead";
			break;
		case WAIT_EVENT_REORDER_BUFFER_WRITE:
			event_name = "ReorderBufferWrite";
			break;
		case WAIT_EVENT_REORDER_LOGICAL_MAPPING_READ:
			event_name = "ReorderLogicalMappingRead";
			break;
		case WAIT_EVENT_REPLICATION_SLOT_READ:
			event_name = "ReplicationSlotRead";
			break;
		case WAIT_EVENT_REPLICATION_SLOT_RESTORE_SYNC:
			event_name = "ReplicationSlotRestoreSync";
			break;
		case WAIT_EVENT_REPLICATION_SLOT_SYNC:
			event_name = "ReplicationSlotSync";
			break;
		case WAIT_EVENT_REPLICATION_SLOT_WRITE:
			event_name = "ReplicationSlotWrite";
			break;
		case WAIT_EVENT_SLRU_FLUSH_SYNC:
			event_name = "SLRUFlushSync";
			break;
		case WAIT_EVENT_SLRU_READ:
			event_name = "SLRURead";
			break;
		case WAIT_EVENT_SLRU_SYNC:
			event_name = "SLRUSync";
			break;
		case WAIT_EVENT_SLRU_WRITE:
			event_name = "SLRUWrite";
			break;
		case WAIT_EVENT_SNAPBUILD_READ:
			event_name = "SnapbuildRead";
			break;
		case WAIT_EVENT_SNAPBUILD_SYNC:
			event_name = "SnapbuildSync";
			break;
		case WAIT_EVENT_SNAPBUILD_WRITE:
			event_name = "SnapbuildWrite";
			break;
		case WAIT_EVENT_TIMELINE_HISTORY_FILE_SYNC:
			event_name = "TimelineHistoryFileSync";
			break;
		case WAIT_EVENT_TIMELINE_HISTORY_FILE_WRITE:
			event_name = "TimelineHistoryFileWrite";
			break;
		case WAIT_EVENT_TIMELINE_HISTORY_READ:
			event_name = "TimelineHistoryRead";
			break;
		case WAIT_EVENT_TIMELINE_HISTORY_SYNC:
			event_name = "TimelineHistorySync";
			break;
		case WAIT_EVENT_TIMELINE_HISTORY_WRITE:
			event_name = "TimelineHistoryWrite";
			break;
		case WAIT_EVENT_TWOPHASE_FILE_READ:
			event_name = "TwophaseFileRead";
			break;
		case WAIT_EVENT_TWOPHASE_FILE_SYNC:
			event_name = "TwophaseFileSync";
			break;
		case WAIT_EVENT_TWOPHASE_FILE_WRITE:
			event_name = "TwophaseFileWrite";
			break;
		case WAIT_EVENT_WALSENDER_TIMELINE_HISTORY_READ:
			event_name = "WALSenderTimelineHistoryRead";
			break;
		case WAIT_EVENT_WAL_BOOTSTRAP_SYNC:
			event_name = "WALBootstrapSync";
			break;
		case WAIT_EVENT_WAL_BOOTSTRAP_WRITE:
			event_name = "WALBootstrapWrite";
			break;
		case WAIT_EVENT_WAL_COPY_READ:
			event_name = "WALCopyRead";
			break;
		case WAIT_EVENT_WAL_COPY_SYNC:
			event_name = "WALCopySync";
			break;
		case WAIT_EVENT_WAL_COPY_WRITE:
			event_name = "WALCopyWrite";
			break;
		case WAIT_EVENT_WAL_INIT_SYNC:
			event_name = "WALInitSync";
			break;
		case WAIT_EVENT_WAL_INIT_WRITE:
			event_name = "WALInitWrite";
			break;
		case WAIT_EVENT_WAL_READ:
			event_name = "WALRead";
			break;
		case WAIT_EVENT_WAL_SYNC:
			event_name = "WALSync";
			break;
		case WAIT_EVENT_WAL_SYNC_METHOD_ASSIGN:
			event_name = "WALSyncMethodAssign";
			break;
		case WAIT_EVENT_WAL_WRITE:
			event_name = "WALWrite";
			break;

			/* no default case, so that compiler will warn */
	}

	return event_name;
}