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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  fn ;
typedef  int /*<<< orphan*/  XLogSegNo ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  Walfile ;
struct TYPE_5__ {char* partial_suffix; TYPE_1__* walmethod; int /*<<< orphan*/  timeline; } ;
struct TYPE_4__ {scalar_t__ (* get_file_size ) (char*) ;scalar_t__ (* sync ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* getlasterror ) () ;int /*<<< orphan*/ * (* open_for_write ) (char*,char*,scalar_t__) ;int /*<<< orphan*/  (* close ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ (* existsfile ) (char*) ;} ;
typedef  TYPE_2__ StreamCtl ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_UNLINK ; 
 scalar_t__ ENOSPC ; 
 int MAXPGPATH ; 
 scalar_t__ WalSegSz ; 
 int /*<<< orphan*/  XLByteToSeg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XLogFileName (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 char* current_walfile_name ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ngettext (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*,int,...) ; 
 int /*<<< orphan*/  pg_log_fatal (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ stub1 (char*) ; 
 int /*<<< orphan*/  stub10 () ; 
 scalar_t__ stub2 (char*) ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/ * stub4 (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub5 () ; 
 scalar_t__ stub6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 () ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub9 (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/ * walfile ; 

__attribute__((used)) static bool
open_walfile(StreamCtl *stream, XLogRecPtr startpoint)
{
	Walfile    *f;
	char		fn[MAXPGPATH];
	ssize_t		size;
	XLogSegNo	segno;

	XLByteToSeg(startpoint, segno, WalSegSz);
	XLogFileName(current_walfile_name, stream->timeline, segno, WalSegSz);

	snprintf(fn, sizeof(fn), "%s%s", current_walfile_name,
			 stream->partial_suffix ? stream->partial_suffix : "");

	/*
	 * When streaming to files, if an existing file exists we verify that it's
	 * either empty (just created), or a complete WalSegSz segment (in which
	 * case it has been created and padded). Anything else indicates a corrupt
	 * file.
	 *
	 * When streaming to tar, no file with this name will exist before, so we
	 * never have to verify a size.
	 */
	if (stream->walmethod->existsfile(fn))
	{
		size = stream->walmethod->get_file_size(fn);
		if (size < 0)
		{
			pg_log_error("could not get size of write-ahead log file \"%s\": %s",
						 fn, stream->walmethod->getlasterror());
			return false;
		}
		if (size == WalSegSz)
		{
			/* Already padded file. Open it for use */
			f = stream->walmethod->open_for_write(current_walfile_name, stream->partial_suffix, 0);
			if (f == NULL)
			{
				pg_log_error("could not open existing write-ahead log file \"%s\": %s",
							 fn, stream->walmethod->getlasterror());
				return false;
			}

			/* fsync file in case of a previous crash */
			if (stream->walmethod->sync(f) != 0)
			{
				pg_log_fatal("could not fsync existing write-ahead log file \"%s\": %s",
							 fn, stream->walmethod->getlasterror());
				stream->walmethod->close(f, CLOSE_UNLINK);
				exit(1);
			}

			walfile = f;
			return true;
		}
		if (size != 0)
		{
			/* if write didn't set errno, assume problem is no disk space */
			if (errno == 0)
				errno = ENOSPC;
			pg_log_error(ngettext("write-ahead log file \"%s\" has %d byte, should be 0 or %d",
								  "write-ahead log file \"%s\" has %d bytes, should be 0 or %d",
								  size),
						 fn, (int) size, WalSegSz);
			return false;
		}
		/* File existed and was empty, so fall through and open */
	}

	/* No file existed, so create one */

	f = stream->walmethod->open_for_write(current_walfile_name,
										  stream->partial_suffix, WalSegSz);
	if (f == NULL)
	{
		pg_log_error("could not open write-ahead log file \"%s\": %s",
					 fn, stream->walmethod->getlasterror());
		return false;
	}

	walfile = f;
	return true;
}