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
struct stat {int dummy; } ;

/* Variables and functions */
 int ArchiveRecoveryRequested ; 
 int BasicOpenFilePerm (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  FATAL ; 
 scalar_t__ IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int O_RDWR ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  RECOVERY_COMMAND_DONE ; 
 int /*<<< orphan*/  RECOVERY_COMMAND_FILE ; 
 int /*<<< orphan*/  RECOVERY_SIGNAL_FILE ; 
 int /*<<< orphan*/  STANDBY_SIGNAL_FILE ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int StandbyModeRequested ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int get_sync_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_fsync (int) ; 
 int recovery_signal_file_found ; 
 int standby_signal_file_found ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  sync_method ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
readRecoverySignalFile(void)
{
	struct stat stat_buf;

	if (IsBootstrapProcessingMode())
		return;

	/*
	 * Check for old recovery API file: recovery.conf
	 */
	if (stat(RECOVERY_COMMAND_FILE, &stat_buf) == 0)
		ereport(FATAL,
				(errcode_for_file_access(),
				 errmsg("using recovery command file \"%s\" is not supported",
						RECOVERY_COMMAND_FILE)));

	/*
	 * Remove unused .done file, if present. Ignore if absent.
	 */
	unlink(RECOVERY_COMMAND_DONE);

	/*
	 * Check for recovery signal files and if found, fsync them since they
	 * represent server state information.  We don't sweat too much about the
	 * possibility of fsync failure, however.
	 *
	 * If present, standby signal file takes precedence. If neither is present
	 * then we won't enter archive recovery.
	 */
	if (stat(STANDBY_SIGNAL_FILE, &stat_buf) == 0)
	{
		int			fd;

		fd = BasicOpenFilePerm(STANDBY_SIGNAL_FILE, O_RDWR | PG_BINARY | get_sync_bit(sync_method),
							   S_IRUSR | S_IWUSR);
		if (fd >= 0)
		{
			(void) pg_fsync(fd);
			close(fd);
		}
		standby_signal_file_found = true;
	}
	else if (stat(RECOVERY_SIGNAL_FILE, &stat_buf) == 0)
	{
		int			fd;

		fd = BasicOpenFilePerm(RECOVERY_SIGNAL_FILE, O_RDWR | PG_BINARY | get_sync_bit(sync_method),
							   S_IRUSR | S_IWUSR);
		if (fd >= 0)
		{
			(void) pg_fsync(fd);
			close(fd);
		}
		recovery_signal_file_found = true;
	}

	StandbyModeRequested = false;
	ArchiveRecoveryRequested = false;
	if (standby_signal_file_found)
	{
		StandbyModeRequested = true;
		ArchiveRecoveryRequested = true;
	}
	else if (recovery_signal_file_found)
	{
		StandbyModeRequested = false;
		ArchiveRecoveryRequested = true;
	}
	else
		return;

	/*
	 * We don't support standby mode in standalone backends; that requires
	 * other processes such as the WAL receiver to be alive.
	 */
	if (StandbyModeRequested && !IsUnderPostmaster)
		ereport(FATAL,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("standby mode is not supported by single-user servers")));
}