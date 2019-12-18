#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ system_identifier; scalar_t__ pg_control_version; scalar_t__ catalog_version_no; scalar_t__ state; } ;
struct TYPE_3__ {scalar_t__ system_identifier; scalar_t__ pg_control_version; scalar_t__ catalog_version_no; scalar_t__ data_checksum_version; scalar_t__ state; int /*<<< orphan*/  wal_log_hints; } ;

/* Variables and functions */
 scalar_t__ CATALOG_VERSION_NO ; 
 TYPE_2__ ControlFile_source ; 
 TYPE_1__ ControlFile_target ; 
 scalar_t__ DB_SHUTDOWNED ; 
 scalar_t__ DB_SHUTDOWNED_IN_RECOVERY ; 
 scalar_t__ PG_CONTROL_VERSION ; 
 scalar_t__ PG_DATA_CHECKSUM_VERSION ; 
 scalar_t__ datadir_source ; 
 int /*<<< orphan*/  pg_fatal (char*) ; 

__attribute__((used)) static void
sanityChecks(void)
{
	/* TODO Check that there's no backup_label in either cluster */

	/* Check system_identifier match */
	if (ControlFile_target.system_identifier != ControlFile_source.system_identifier)
		pg_fatal("source and target clusters are from different systems");

	/* check version */
	if (ControlFile_target.pg_control_version != PG_CONTROL_VERSION ||
		ControlFile_source.pg_control_version != PG_CONTROL_VERSION ||
		ControlFile_target.catalog_version_no != CATALOG_VERSION_NO ||
		ControlFile_source.catalog_version_no != CATALOG_VERSION_NO)
	{
		pg_fatal("clusters are not compatible with this version of pg_rewind");
	}

	/*
	 * Target cluster need to use checksums or hint bit wal-logging, this to
	 * prevent from data corruption that could occur because of hint bits.
	 */
	if (ControlFile_target.data_checksum_version != PG_DATA_CHECKSUM_VERSION &&
		!ControlFile_target.wal_log_hints)
	{
		pg_fatal("target server needs to use either data checksums or \"wal_log_hints = on\"");
	}

	/*
	 * Target cluster better not be running. This doesn't guard against
	 * someone starting the cluster concurrently. Also, this is probably more
	 * strict than necessary; it's OK if the target node was not shut down
	 * cleanly, as long as it isn't running at the moment.
	 */
	if (ControlFile_target.state != DB_SHUTDOWNED &&
		ControlFile_target.state != DB_SHUTDOWNED_IN_RECOVERY)
		pg_fatal("target server must be shut down cleanly");

	/*
	 * When the source is a data directory, also require that the source
	 * server is shut down. There isn't any very strong reason for this
	 * limitation, but better safe than sorry.
	 */
	if (datadir_source &&
		ControlFile_source.state != DB_SHUTDOWNED &&
		ControlFile_source.state != DB_SHUTDOWNED_IN_RECOVERY)
		pg_fatal("source data directory must be shut down cleanly");
}