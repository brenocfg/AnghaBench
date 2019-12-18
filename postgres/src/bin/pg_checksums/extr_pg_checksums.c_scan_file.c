#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_7__ {scalar_t__ data_checksum_version; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  pd_checksum; } ;
typedef  TYPE_1__* PageHeader ;
typedef  TYPE_2__ PGAlignedBlock ;
typedef  int BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BLCKSZ ; 
 TYPE_4__* ControlFile ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int PG_BINARY ; 
 scalar_t__ PG_DATA_CHECKSUM_VERSION ; 
 scalar_t__ PG_MODE_CHECK ; 
 scalar_t__ PG_MODE_ENABLE ; 
 scalar_t__ PageIsNew (TYPE_1__*) ; 
 int RELSEG_SIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  badblocks ; 
 int /*<<< orphan*/  blocks ; 
 int /*<<< orphan*/  close (int) ; 
 int current_size ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  files ; 
 scalar_t__ lseek (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mode ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_checksum_page (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  pg_log_info (char*,char const*) ; 
 int /*<<< orphan*/  progress_report (int) ; 
 int read (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ showprogress ; 
 scalar_t__ verbose ; 
 int write (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
scan_file(const char *fn, BlockNumber segmentno)
{
	PGAlignedBlock buf;
	PageHeader	header = (PageHeader) buf.data;
	int			f;
	BlockNumber blockno;
	int			flags;

	Assert(mode == PG_MODE_ENABLE ||
		   mode == PG_MODE_CHECK);

	flags = (mode == PG_MODE_ENABLE) ? O_RDWR : O_RDONLY;
	f = open(fn, PG_BINARY | flags, 0);

	if (f < 0)
	{
		pg_log_error("could not open file \"%s\": %m", fn);
		exit(1);
	}

	files++;

	for (blockno = 0;; blockno++)
	{
		uint16		csum;
		int			r = read(f, buf.data, BLCKSZ);

		if (r == 0)
			break;
		if (r != BLCKSZ)
		{
			if (r < 0)
				pg_log_error("could not read block %u in file \"%s\": %m",
							 blockno, fn);
			else
				pg_log_error("could not read block %u in file \"%s\": read %d of %d",
							 blockno, fn, r, BLCKSZ);
			exit(1);
		}
		blocks++;

		/* New pages have no checksum yet */
		if (PageIsNew(header))
			continue;

		csum = pg_checksum_page(buf.data, blockno + segmentno * RELSEG_SIZE);
		current_size += r;
		if (mode == PG_MODE_CHECK)
		{
			if (csum != header->pd_checksum)
			{
				if (ControlFile->data_checksum_version == PG_DATA_CHECKSUM_VERSION)
					pg_log_error("checksum verification failed in file \"%s\", block %u: calculated checksum %X but block contains %X",
								 fn, blockno, csum, header->pd_checksum);
				badblocks++;
			}
		}
		else if (mode == PG_MODE_ENABLE)
		{
			int		w;

			/* Set checksum in page header */
			header->pd_checksum = csum;

			/* Seek back to beginning of block */
			if (lseek(f, -BLCKSZ, SEEK_CUR) < 0)
			{
				pg_log_error("seek failed for block %u in file \"%s\": %m", blockno, fn);
				exit(1);
			}

			/* Write block with checksum */
			w = write(f, buf.data, BLCKSZ);
			if (w != BLCKSZ)
			{
				if (w < 0)
					pg_log_error("could not write block %u in file \"%s\": %m",
								 blockno, fn);
				else
					pg_log_error("could not write block %u in file \"%s\": wrote %d of %d",
								 blockno, fn, w, BLCKSZ);
				exit(1);
			}
		}

		if (showprogress)
			progress_report(false);
	}

	if (verbose)
	{
		if (mode == PG_MODE_CHECK)
			pg_log_info("checksums verified in file \"%s\"", fn);
		if (mode == PG_MODE_ENABLE)
			pg_log_info("checksums enabled in file \"%s\"", fn);
	}

	close(f);
}