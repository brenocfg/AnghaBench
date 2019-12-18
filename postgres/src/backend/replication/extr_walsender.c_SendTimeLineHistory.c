#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rbuf ;
typedef  scalar_t__ off_t ;
struct TYPE_4__ {int /*<<< orphan*/  timeline; } ;
typedef  TYPE_1__ TimeLineHistoryCmd ;
struct TYPE_5__ {char* data; } ;
typedef  int /*<<< orphan*/  StringInfoData ;
typedef  int Size ;
typedef  TYPE_2__ PGAlignedBlock ;

/* Variables and functions */
 scalar_t__ BYTEAOID ; 
 scalar_t__ CloseTransientFile (int) ; 
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int MAXFNAMELEN ; 
 int MAXPGPATH ; 
 int O_RDONLY ; 
 int OpenTransientFile (char*,int) ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ TEXTOID ; 
 int /*<<< orphan*/  TLHistoryFileName (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLHistoryFilePath (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_WALSENDER_TIMELINE_HISTORY_READ ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_beginmessage (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendbytes (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pq_sendint16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ *,char*) ; 
 int read (int,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
SendTimeLineHistory(TimeLineHistoryCmd *cmd)
{
	StringInfoData buf;
	char		histfname[MAXFNAMELEN];
	char		path[MAXPGPATH];
	int			fd;
	off_t		histfilelen;
	off_t		bytesleft;
	Size		len;

	/*
	 * Reply with a result set with one row, and two columns. The first col is
	 * the name of the history file, 2nd is the contents.
	 */

	TLHistoryFileName(histfname, cmd->timeline);
	TLHistoryFilePath(path, cmd->timeline);

	/* Send a RowDescription message */
	pq_beginmessage(&buf, 'T');
	pq_sendint16(&buf, 2);		/* 2 fields */

	/* first field */
	pq_sendstring(&buf, "filename");	/* col name */
	pq_sendint32(&buf, 0);		/* table oid */
	pq_sendint16(&buf, 0);		/* attnum */
	pq_sendint32(&buf, TEXTOID);	/* type oid */
	pq_sendint16(&buf, -1);		/* typlen */
	pq_sendint32(&buf, 0);		/* typmod */
	pq_sendint16(&buf, 0);		/* format code */

	/* second field */
	pq_sendstring(&buf, "content"); /* col name */
	pq_sendint32(&buf, 0);		/* table oid */
	pq_sendint16(&buf, 0);		/* attnum */
	pq_sendint32(&buf, BYTEAOID);	/* type oid */
	pq_sendint16(&buf, -1);		/* typlen */
	pq_sendint32(&buf, 0);		/* typmod */
	pq_sendint16(&buf, 0);		/* format code */
	pq_endmessage(&buf);

	/* Send a DataRow message */
	pq_beginmessage(&buf, 'D');
	pq_sendint16(&buf, 2);		/* # of columns */
	len = strlen(histfname);
	pq_sendint32(&buf, len);	/* col1 len */
	pq_sendbytes(&buf, histfname, len);

	fd = OpenTransientFile(path, O_RDONLY | PG_BINARY);
	if (fd < 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not open file \"%s\": %m", path)));

	/* Determine file length and send it to client */
	histfilelen = lseek(fd, 0, SEEK_END);
	if (histfilelen < 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not seek to end of file \"%s\": %m", path)));
	if (lseek(fd, 0, SEEK_SET) != 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not seek to beginning of file \"%s\": %m", path)));

	pq_sendint32(&buf, histfilelen);	/* col2 len */

	bytesleft = histfilelen;
	while (bytesleft > 0)
	{
		PGAlignedBlock rbuf;
		int			nread;

		pgstat_report_wait_start(WAIT_EVENT_WALSENDER_TIMELINE_HISTORY_READ);
		nread = read(fd, rbuf.data, sizeof(rbuf));
		pgstat_report_wait_end();
		if (nread < 0)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not read file \"%s\": %m",
							path)));
		else if (nread == 0)
			ereport(ERROR,
					(errcode(ERRCODE_DATA_CORRUPTED),
					 errmsg("could not read file \"%s\": read %d of %zu",
							path, nread, (Size) bytesleft)));

		pq_sendbytes(&buf, rbuf.data, nread);
		bytesleft -= nread;
	}

	if (CloseTransientFile(fd) != 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not close file \"%s\": %m", path)));

	pq_endmessage(&buf);
}