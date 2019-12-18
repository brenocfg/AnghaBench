#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int st_size; } ;

/* Variables and functions */
 scalar_t__ IsXLogFileName (int /*<<< orphan*/ ) ; 
 scalar_t__ SetWALFileNameForCleanup () ; 
 scalar_t__ SetWALSegSize () ; 
 int /*<<< orphan*/  WALFilePath ; 
 int WalSegSz ; 
 int /*<<< orphan*/  XLOG_DATA ; 
 char* _ (char*) ; 
 scalar_t__ debug ; 
 char* exclusiveCleanupFileName ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ need_cleanup ; 
 int /*<<< orphan*/  nextWALFileName ; 
 int /*<<< orphan*/  nextWALFileType ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 long sleeptime ; 
 scalar_t__ stat (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ stat_buf ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool
CustomizableNextWALFileReady(void)
{
	if (stat(WALFilePath, &stat_buf) == 0)
	{
		/*
		 * If we've not seen any WAL segments, we don't know the WAL segment
		 * size, which we need. If it looks like a WAL segment, determine size
		 * of segments for the cluster.
		 */
		if (WalSegSz == -1 && IsXLogFileName(nextWALFileName))
		{
			if (SetWALSegSize())
			{
				/*
				 * Successfully determined WAL segment size. Can compute
				 * cleanup cutoff now.
				 */
				need_cleanup = SetWALFileNameForCleanup();
				if (debug)
				{
					fprintf(stderr,
							_("WAL segment size:     %d \n"), WalSegSz);
					fprintf(stderr, "Keep archive history: ");

					if (need_cleanup)
						fprintf(stderr, "%s and later\n",
								exclusiveCleanupFileName);
					else
						fprintf(stderr, "no cleanup required\n");
				}
			}
		}

		/*
		 * Return only if it's the right size already.
		 */
		if (WalSegSz > 0 && stat_buf.st_size == WalSegSz)
		{
#ifdef WIN32

			/*
			 * Windows 'cp' sets the final file size before the copy is
			 * complete, and not yet ready to be opened by pg_standby. So we
			 * wait for sleeptime secs before attempting to restore. If that
			 * is not enough, we will rely on the retry/holdoff mechanism.
			 * GNUWin32's cp does not have this problem.
			 */
			pg_usleep(sleeptime * 1000000L);
#endif
			nextWALFileType = XLOG_DATA;
			return true;
		}

		/*
		 * If still too small, wait until it is the correct size
		 */
		if (WalSegSz > 0 && stat_buf.st_size > WalSegSz)
		{
			if (debug)
			{
				fprintf(stderr, "file size greater than expected\n");
				fflush(stderr);
			}
			exit(3);
		}
	}

	return false;
}