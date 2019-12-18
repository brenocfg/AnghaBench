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
typedef  int /*<<< orphan*/  Walfile ;
struct TYPE_6__ {char* timeline; scalar_t__ mark_done; TYPE_1__* walmethod; } ;
struct TYPE_5__ {char* (* getlasterror ) () ;scalar_t__ (* close ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ (* write ) (int /*<<< orphan*/ *,char*,int) ;int /*<<< orphan*/ * (* open_for_write ) (char*,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ StreamCtl ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_NORMAL ; 
 int /*<<< orphan*/  CLOSE_UNLINK ; 
 int MAXFNAMELEN ; 
 int /*<<< orphan*/  TLHistoryFileName (char*,char*) ; 
 int /*<<< orphan*/  mark_file_as_archived (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * stub1 (char*,char*,int /*<<< orphan*/ ) ; 
 char* stub2 () ; 
 scalar_t__ stub3 (int /*<<< orphan*/ *,char*,int) ; 
 char* stub4 () ; 
 scalar_t__ stub5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* stub7 () ; 

__attribute__((used)) static bool
writeTimeLineHistoryFile(StreamCtl *stream, char *filename, char *content)
{
	int			size = strlen(content);
	char		histfname[MAXFNAMELEN];
	Walfile    *f;

	/*
	 * Check that the server's idea of how timeline history files should be
	 * named matches ours.
	 */
	TLHistoryFileName(histfname, stream->timeline);
	if (strcmp(histfname, filename) != 0)
	{
		pg_log_error("server reported unexpected history file name for timeline %u: %s",
					 stream->timeline, filename);
		return false;
	}

	f = stream->walmethod->open_for_write(histfname, ".tmp", 0);
	if (f == NULL)
	{
		pg_log_error("could not create timeline history file \"%s\": %s",
					 histfname, stream->walmethod->getlasterror());
		return false;
	}

	if ((int) stream->walmethod->write(f, content, size) != size)
	{
		pg_log_error("could not write timeline history file \"%s\": %s",
					 histfname, stream->walmethod->getlasterror());

		/*
		 * If we fail to make the file, delete it to release disk space
		 */
		stream->walmethod->close(f, CLOSE_UNLINK);

		return false;
	}

	if (stream->walmethod->close(f, CLOSE_NORMAL) != 0)
	{
		pg_log_error("could not close file \"%s\": %s",
					 histfname, stream->walmethod->getlasterror());
		return false;
	}

	/* Maintain archive_status, check close_walfile() for details. */
	if (stream->mark_done)
	{
		/* writes error message if failed */
		if (!mark_file_as_archived(stream, histfname))
			return false;
	}

	return true;
}