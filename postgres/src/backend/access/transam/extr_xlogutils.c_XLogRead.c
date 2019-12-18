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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  XLogSegNo ;
typedef  int XLogRecPtr ;
typedef  scalar_t__ TimeLineID ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BasicOpenFile (char*,int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  ERROR ; 
 int MAXPGPATH ; 
 int O_RDONLY ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  WAIT_EVENT_WAL_READ ; 
 int /*<<< orphan*/  XLByteInSeg (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLByteToSeg (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogFilePath (char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XLogSegmentOffset (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 int errno ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int wal_segment_size ; 

__attribute__((used)) static void
XLogRead(char *buf, int segsize, TimeLineID tli, XLogRecPtr startptr,
		 Size count)
{
	char	   *p;
	XLogRecPtr	recptr;
	Size		nbytes;

	/* state maintained across calls */
	static int	sendFile = -1;
	static XLogSegNo sendSegNo = 0;
	static TimeLineID sendTLI = 0;
	static uint32 sendOff = 0;

	Assert(segsize == wal_segment_size);

	p = buf;
	recptr = startptr;
	nbytes = count;

	while (nbytes > 0)
	{
		uint32		startoff;
		int			segbytes;
		int			readbytes;

		startoff = XLogSegmentOffset(recptr, segsize);

		/* Do we need to switch to a different xlog segment? */
		if (sendFile < 0 || !XLByteInSeg(recptr, sendSegNo, segsize) ||
			sendTLI != tli)
		{
			char		path[MAXPGPATH];

			if (sendFile >= 0)
				close(sendFile);

			XLByteToSeg(recptr, sendSegNo, segsize);

			XLogFilePath(path, tli, sendSegNo, segsize);

			sendFile = BasicOpenFile(path, O_RDONLY | PG_BINARY);

			if (sendFile < 0)
			{
				if (errno == ENOENT)
					ereport(ERROR,
							(errcode_for_file_access(),
							 errmsg("requested WAL segment %s has already been removed",
									path)));
				else
					ereport(ERROR,
							(errcode_for_file_access(),
							 errmsg("could not open file \"%s\": %m",
									path)));
			}
			sendOff = 0;
			sendTLI = tli;
		}

		/* Need to seek in the file? */
		if (sendOff != startoff)
		{
			if (lseek(sendFile, (off_t) startoff, SEEK_SET) < 0)
			{
				char		path[MAXPGPATH];
				int			save_errno = errno;

				XLogFilePath(path, tli, sendSegNo, segsize);
				errno = save_errno;
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not seek in log segment %s to offset %u: %m",
								path, startoff)));
			}
			sendOff = startoff;
		}

		/* How many bytes are within this segment? */
		if (nbytes > (segsize - startoff))
			segbytes = segsize - startoff;
		else
			segbytes = nbytes;

		pgstat_report_wait_start(WAIT_EVENT_WAL_READ);
		readbytes = read(sendFile, p, segbytes);
		pgstat_report_wait_end();
		if (readbytes <= 0)
		{
			char		path[MAXPGPATH];
			int			save_errno = errno;

			XLogFilePath(path, tli, sendSegNo, segsize);
			errno = save_errno;
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not read from log segment %s, offset %u, length %lu: %m",
							path, sendOff, (unsigned long) segbytes)));
		}

		/* Update state for read */
		recptr += readbytes;

		sendOff += readbytes;
		nbytes -= readbytes;
		p += readbytes;
	}
}