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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  strfbuf ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  XLogSegNo ;
typedef  int XLogRecPtr ;
typedef  int /*<<< orphan*/  TimeLineID ;

/* Variables and functions */
 int MAXFNAMELEN ; 
 int /*<<< orphan*/  WalSegSz ; 
 int /*<<< orphan*/  XLByteToSeg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogFileName (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_target_file () ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_target_file (char*,int) ; 
 int /*<<< orphan*/  pg_fatal (char*) ; 
 int snprintf (char*,int,char*,int,int,char*,int,int,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_target_range (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
createBackupLabel(XLogRecPtr startpoint, TimeLineID starttli, XLogRecPtr checkpointloc)
{
	XLogSegNo	startsegno;
	time_t		stamp_time;
	char		strfbuf[128];
	char		xlogfilename[MAXFNAMELEN];
	struct tm  *tmp;
	char		buf[1000];
	int			len;

	XLByteToSeg(startpoint, startsegno, WalSegSz);
	XLogFileName(xlogfilename, starttli, startsegno, WalSegSz);

	/*
	 * Construct backup label file
	 */
	stamp_time = time(NULL);
	tmp = localtime(&stamp_time);
	strftime(strfbuf, sizeof(strfbuf), "%Y-%m-%d %H:%M:%S %Z", tmp);

	len = snprintf(buf, sizeof(buf),
				   "START WAL LOCATION: %X/%X (file %s)\n"
				   "CHECKPOINT LOCATION: %X/%X\n"
				   "BACKUP METHOD: pg_rewind\n"
				   "BACKUP FROM: standby\n"
				   "START TIME: %s\n",
	/* omit LABEL: line */
				   (uint32) (startpoint >> 32), (uint32) startpoint, xlogfilename,
				   (uint32) (checkpointloc >> 32), (uint32) checkpointloc,
				   strfbuf);
	if (len >= sizeof(buf))
		pg_fatal("backup label buffer too small");	/* shouldn't happen */

	/* TODO: move old file out of the way, if any. */
	open_target_file("backup_label", true); /* BACKUP_LABEL_FILE */
	write_target_range(buf, 0, len);
	close_target_file();
}