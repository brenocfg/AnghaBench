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
struct TYPE_7__ {int keysize; int entrysize; } ;
struct TYPE_6__ {void* functions; void* tables; scalar_t__ stats_timestamp; int /*<<< orphan*/  stat_reset_timestamp; scalar_t__ n_block_write_time; scalar_t__ n_block_read_time; scalar_t__ last_checksum_failure; scalar_t__ n_checksum_failures; scalar_t__ n_deadlocks; scalar_t__ n_temp_bytes; scalar_t__ n_temp_files; scalar_t__ n_conflict_startup_deadlock; scalar_t__ n_conflict_bufferpin; scalar_t__ n_conflict_snapshot; scalar_t__ n_conflict_lock; scalar_t__ n_conflict_tablespace; scalar_t__ last_autovac_time; scalar_t__ n_tuples_deleted; scalar_t__ n_tuples_updated; scalar_t__ n_tuples_inserted; scalar_t__ n_tuples_fetched; scalar_t__ n_tuples_returned; scalar_t__ n_blocks_hit; scalar_t__ n_blocks_fetched; scalar_t__ n_xact_rollback; scalar_t__ n_xact_commit; } ;
typedef  int /*<<< orphan*/  PgStat_StatTabEntry ;
typedef  int /*<<< orphan*/  PgStat_StatFuncEntry ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  PGSTAT_FUNCTION_HASH_SIZE ; 
 int /*<<< orphan*/  PGSTAT_TAB_HASH_SIZE ; 
 void* hash_create (char*,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
reset_dbentry_counters(PgStat_StatDBEntry *dbentry)
{
	HASHCTL		hash_ctl;

	dbentry->n_xact_commit = 0;
	dbentry->n_xact_rollback = 0;
	dbentry->n_blocks_fetched = 0;
	dbentry->n_blocks_hit = 0;
	dbentry->n_tuples_returned = 0;
	dbentry->n_tuples_fetched = 0;
	dbentry->n_tuples_inserted = 0;
	dbentry->n_tuples_updated = 0;
	dbentry->n_tuples_deleted = 0;
	dbentry->last_autovac_time = 0;
	dbentry->n_conflict_tablespace = 0;
	dbentry->n_conflict_lock = 0;
	dbentry->n_conflict_snapshot = 0;
	dbentry->n_conflict_bufferpin = 0;
	dbentry->n_conflict_startup_deadlock = 0;
	dbentry->n_temp_files = 0;
	dbentry->n_temp_bytes = 0;
	dbentry->n_deadlocks = 0;
	dbentry->n_checksum_failures = 0;
	dbentry->last_checksum_failure = 0;
	dbentry->n_block_read_time = 0;
	dbentry->n_block_write_time = 0;

	dbentry->stat_reset_timestamp = GetCurrentTimestamp();
	dbentry->stats_timestamp = 0;

	memset(&hash_ctl, 0, sizeof(hash_ctl));
	hash_ctl.keysize = sizeof(Oid);
	hash_ctl.entrysize = sizeof(PgStat_StatTabEntry);
	dbentry->tables = hash_create("Per-database table",
								  PGSTAT_TAB_HASH_SIZE,
								  &hash_ctl,
								  HASH_ELEM | HASH_BLOBS);

	hash_ctl.keysize = sizeof(Oid);
	hash_ctl.entrysize = sizeof(PgStat_StatFuncEntry);
	dbentry->functions = hash_create("Per-database function",
									 PGSTAT_FUNCTION_HASH_SIZE,
									 &hash_ctl,
									 HASH_ELEM | HASH_BLOBS);
}