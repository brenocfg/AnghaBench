#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_6__ {scalar_t__ mark_done; TYPE_1__* walmethod; scalar_t__ partial_suffix; } ;
struct TYPE_5__ {int (* get_current_pos ) (int /*<<< orphan*/ *) ;int (* close ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* getlasterror ) () ;} ;
typedef  TYPE_2__ StreamCtl ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_NORMAL ; 
 int /*<<< orphan*/  CLOSE_NO_RENAME ; 
 int /*<<< orphan*/  CLOSE_UNLINK ; 
 int WalSegSz ; 
 int /*<<< orphan*/  current_walfile_name ; 
 int /*<<< orphan*/  lastFlushPosition ; 
 int /*<<< orphan*/  mark_file_as_archived (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_info (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 () ; 
 int stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 () ; 
 int /*<<< orphan*/ * walfile ; 

__attribute__((used)) static bool
close_walfile(StreamCtl *stream, XLogRecPtr pos)
{
	off_t		currpos;
	int			r;

	if (walfile == NULL)
		return true;

	currpos = stream->walmethod->get_current_pos(walfile);
	if (currpos == -1)
	{
		pg_log_error("could not determine seek position in file \"%s\": %s",
					 current_walfile_name, stream->walmethod->getlasterror());
		stream->walmethod->close(walfile, CLOSE_UNLINK);
		walfile = NULL;

		return false;
	}

	if (stream->partial_suffix)
	{
		if (currpos == WalSegSz)
			r = stream->walmethod->close(walfile, CLOSE_NORMAL);
		else
		{
			pg_log_info("not renaming \"%s%s\", segment is not complete",
						current_walfile_name, stream->partial_suffix);
			r = stream->walmethod->close(walfile, CLOSE_NO_RENAME);
		}
	}
	else
		r = stream->walmethod->close(walfile, CLOSE_NORMAL);

	walfile = NULL;

	if (r != 0)
	{
		pg_log_error("could not close file \"%s\": %s",
					 current_walfile_name, stream->walmethod->getlasterror());
		return false;
	}

	/*
	 * Mark file as archived if requested by the caller - pg_basebackup needs
	 * to do so as files can otherwise get archived again after promotion of a
	 * new node. This is in line with walreceiver.c always doing a
	 * XLogArchiveForceDone() after a complete segment.
	 */
	if (currpos == WalSegSz && stream->mark_done)
	{
		/* writes error message if failed */
		if (!mark_file_as_archived(stream, current_walfile_name))
			return false;
	}

	lastFlushPosition = pos;
	return true;
}