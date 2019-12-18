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
 int MAXPGPATH ; 
 int RecoveryInProgress () ; 
 int /*<<< orphan*/  StatusFilePath (char*,char const*,char*) ; 
 int /*<<< orphan*/  XLogArchiveNotify (char const*) ; 
 scalar_t__ XLogArchivingActive () ; 
 scalar_t__ XLogArchivingAlways () ; 
 scalar_t__ stat (char*,struct stat*) ; 

bool
XLogArchiveCheckDone(const char *xlog)
{
	char		archiveStatusPath[MAXPGPATH];
	struct stat stat_buf;
	bool		inRecovery = RecoveryInProgress();

	/*
	 * The file is always deletable if archive_mode is "off".  On standbys
	 * archiving is disabled if archive_mode is "on", and enabled with
	 * "always".  On a primary, archiving is enabled if archive_mode is "on"
	 * or "always".
	 */
	if (!((XLogArchivingActive() && !inRecovery) ||
		  (XLogArchivingAlways() && inRecovery)))
		return true;

	/* First check for .done --- this means archiver is done with it */
	StatusFilePath(archiveStatusPath, xlog, ".done");
	if (stat(archiveStatusPath, &stat_buf) == 0)
		return true;

	/* check for .ready --- this means archiver is still busy with it */
	StatusFilePath(archiveStatusPath, xlog, ".ready");
	if (stat(archiveStatusPath, &stat_buf) == 0)
		return false;

	/* Race condition --- maybe archiver just finished, so recheck */
	StatusFilePath(archiveStatusPath, xlog, ".done");
	if (stat(archiveStatusPath, &stat_buf) == 0)
		return true;

	/* Retry creation of the .ready file */
	XLogArchiveNotify(xlog);
	return false;
}