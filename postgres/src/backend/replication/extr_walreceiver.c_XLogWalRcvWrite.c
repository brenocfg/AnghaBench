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
typedef  int /*<<< orphan*/  off_t ;
typedef  int XLogRecPtr ;
struct TYPE_2__ {int Write; } ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 scalar_t__ ARCHIVE_MODE_ALWAYS ; 
 scalar_t__ ENOSPC ; 
 TYPE_1__ LogstreamResult ; 
 int MAXFNAMELEN ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  ThisTimeLineID ; 
 int /*<<< orphan*/  XLByteInSeg (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLByteToSeg (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogArchiveForceDone (char*) ; 
 scalar_t__ XLogArchiveMode ; 
 int /*<<< orphan*/  XLogArchiveNotify (char*) ; 
 int XLogFileInit (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  XLogFileName (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogFileNameP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XLogSegmentOffset (int,int) ; 
 int /*<<< orphan*/  XLogWalRcvFlush (int) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ errno ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int recvFile ; 
 int /*<<< orphan*/  recvFileTLI ; 
 int recvOff ; 
 int /*<<< orphan*/  recvSegNo ; 
 int wal_segment_size ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
XLogWalRcvWrite(char *buf, Size nbytes, XLogRecPtr recptr)
{
	int			startoff;
	int			byteswritten;

	while (nbytes > 0)
	{
		int			segbytes;

		if (recvFile < 0 || !XLByteInSeg(recptr, recvSegNo, wal_segment_size))
		{
			bool		use_existent;

			/*
			 * fsync() and close current file before we switch to next one. We
			 * would otherwise have to reopen this file to fsync it later
			 */
			if (recvFile >= 0)
			{
				char		xlogfname[MAXFNAMELEN];

				XLogWalRcvFlush(false);

				/*
				 * XLOG segment files will be re-read by recovery in startup
				 * process soon, so we don't advise the OS to release cache
				 * pages associated with the file like XLogFileClose() does.
				 */
				if (close(recvFile) != 0)
					ereport(PANIC,
							(errcode_for_file_access(),
							 errmsg("could not close log segment %s: %m",
									XLogFileNameP(recvFileTLI, recvSegNo))));

				/*
				 * Create .done file forcibly to prevent the streamed segment
				 * from being archived later.
				 */
				XLogFileName(xlogfname, recvFileTLI, recvSegNo, wal_segment_size);
				if (XLogArchiveMode != ARCHIVE_MODE_ALWAYS)
					XLogArchiveForceDone(xlogfname);
				else
					XLogArchiveNotify(xlogfname);
			}
			recvFile = -1;

			/* Create/use new log file */
			XLByteToSeg(recptr, recvSegNo, wal_segment_size);
			use_existent = true;
			recvFile = XLogFileInit(recvSegNo, &use_existent, true);
			recvFileTLI = ThisTimeLineID;
			recvOff = 0;
		}

		/* Calculate the start offset of the received logs */
		startoff = XLogSegmentOffset(recptr, wal_segment_size);

		if (startoff + nbytes > wal_segment_size)
			segbytes = wal_segment_size - startoff;
		else
			segbytes = nbytes;

		/* Need to seek in the file? */
		if (recvOff != startoff)
		{
			if (lseek(recvFile, (off_t) startoff, SEEK_SET) < 0)
				ereport(PANIC,
						(errcode_for_file_access(),
						 errmsg("could not seek in log segment %s to offset %u: %m",
								XLogFileNameP(recvFileTLI, recvSegNo),
								startoff)));
			recvOff = startoff;
		}

		/* OK to write the logs */
		errno = 0;

		byteswritten = write(recvFile, buf, segbytes);
		if (byteswritten <= 0)
		{
			/* if write didn't set errno, assume no disk space */
			if (errno == 0)
				errno = ENOSPC;
			ereport(PANIC,
					(errcode_for_file_access(),
					 errmsg("could not write to log segment %s "
							"at offset %u, length %lu: %m",
							XLogFileNameP(recvFileTLI, recvSegNo),
							recvOff, (unsigned long) segbytes)));
		}

		/* Update state for write */
		recptr += byteswritten;

		recvOff += byteswritten;
		nbytes -= byteswritten;
		buf += byteswritten;

		LogstreamResult.Write = recptr;
	}
}