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
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  SlruCtl ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  ERROR ; 
 int MAXPGPATH ; 
#define  SLRU_CLOSE_FAILED 133 
#define  SLRU_FSYNC_FAILED 132 
#define  SLRU_OPEN_FAILED 131 
 int SLRU_PAGES_PER_SEGMENT ; 
#define  SLRU_READ_FAILED 130 
#define  SLRU_SEEK_FAILED 129 
#define  SLRU_WRITE_FAILED 128 
 int /*<<< orphan*/  SlruFileName (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  data_sync_elevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errdetail (char*,char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int slru_errcause ; 
 int /*<<< orphan*/  slru_errno ; 

__attribute__((used)) static void
SlruReportIOError(SlruCtl ctl, int pageno, TransactionId xid)
{
	int			segno = pageno / SLRU_PAGES_PER_SEGMENT;
	int			rpageno = pageno % SLRU_PAGES_PER_SEGMENT;
	int			offset = rpageno * BLCKSZ;
	char		path[MAXPGPATH];

	SlruFileName(ctl, path, segno);
	errno = slru_errno;
	switch (slru_errcause)
	{
		case SLRU_OPEN_FAILED:
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not access status of transaction %u", xid),
					 errdetail("Could not open file \"%s\": %m.", path)));
			break;
		case SLRU_SEEK_FAILED:
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not access status of transaction %u", xid),
					 errdetail("Could not seek in file \"%s\" to offset %u: %m.",
							   path, offset)));
			break;
		case SLRU_READ_FAILED:
			if (errno)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not access status of transaction %u", xid),
						 errdetail("Could not read from file \"%s\" at offset %u: %m.",
								   path, offset)));
			else
				ereport(ERROR,
						(errmsg("could not access status of transaction %u", xid),
						 errdetail("Could not read from file \"%s\" at offset %u: read too few bytes.", path, offset)));
			break;
		case SLRU_WRITE_FAILED:
			if (errno)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not access status of transaction %u", xid),
						 errdetail("Could not write to file \"%s\" at offset %u: %m.",
								   path, offset)));
			else
				ereport(ERROR,
						(errmsg("could not access status of transaction %u", xid),
						 errdetail("Could not write to file \"%s\" at offset %u: wrote too few bytes.",
								   path, offset)));
			break;
		case SLRU_FSYNC_FAILED:
			ereport(data_sync_elevel(ERROR),
					(errcode_for_file_access(),
					 errmsg("could not access status of transaction %u", xid),
					 errdetail("Could not fsync file \"%s\": %m.",
							   path)));
			break;
		case SLRU_CLOSE_FAILED:
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not access status of transaction %u", xid),
					 errdetail("Could not close file \"%s\": %m.",
							   path)));
			break;
		default:
			/* can't get here, we trust */
			elog(ERROR, "unrecognized SimpleLru error cause: %d",
				 (int) slru_errcause);
			break;
	}
}