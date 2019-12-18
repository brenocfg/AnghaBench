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
typedef  TYPE_1__* XLogLongPageHeader ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int xlp_seg_size; } ;
typedef  TYPE_2__ PGAlignedXLogBlock ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ IsValidWalSegSize (int) ; 
 int /*<<< orphan*/  O_RDWR ; 
 char* WALFilePath ; 
 int WalSegSz ; 
 scalar_t__ XLOG_BLCKSZ ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ debug ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* progname ; 
 scalar_t__ read (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static bool
SetWALSegSize(void)
{
	bool		ret_val = false;
	int			fd;
	PGAlignedXLogBlock buf;

	Assert(WalSegSz == -1);

	if ((fd = open(WALFilePath, O_RDWR, 0)) < 0)
	{
		fprintf(stderr, "%s: could not open WAL file \"%s\": %s\n",
				progname, WALFilePath, strerror(errno));
		return false;
	}

	errno = 0;
	if (read(fd, buf.data, XLOG_BLCKSZ) == XLOG_BLCKSZ)
	{
		XLogLongPageHeader longhdr = (XLogLongPageHeader) buf.data;

		WalSegSz = longhdr->xlp_seg_size;

		if (IsValidWalSegSize(WalSegSz))
		{
			/* successfully retrieved WAL segment size */
			ret_val = true;
		}
		else
			fprintf(stderr,
					"%s: WAL segment size must be a power of two between 1MB and 1GB, but the WAL file header specifies %d bytes\n",
					progname, WalSegSz);
	}
	else
	{
		/*
		 * Don't complain loudly, this is to be expected for segments being
		 * created.
		 */
		if (errno != 0)
		{
			if (debug)
				fprintf(stderr, "could not read file \"%s\": %s\n",
						WALFilePath, strerror(errno));
		}
		else
		{
			if (debug)
				fprintf(stderr, "not enough data in file \"%s\"\n",
						WALFilePath);
		}
	}

	fflush(stderr);

	close(fd);
	return ret_val;
}