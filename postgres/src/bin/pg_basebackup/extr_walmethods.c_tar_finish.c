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
typedef  int /*<<< orphan*/  zerobuf ;
struct TYPE_5__ {scalar_t__ avail_out; scalar_t__ avail_in; int /*<<< orphan*/ * next_in; } ;
struct TYPE_4__ {int fd; char* zlibOut; int /*<<< orphan*/  tarfilename; scalar_t__ sync; TYPE_2__* zp; int /*<<< orphan*/  compression; scalar_t__ currentfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_NORMAL ; 
 scalar_t__ ENOSPC ; 
 int /*<<< orphan*/  MemSet (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ZLIB_OUT_SIZE ; 
 int /*<<< orphan*/  Z_FINISH ; 
 scalar_t__ Z_OK ; 
 int Z_STREAM_END ; 
 int Z_STREAM_ERROR ; 
 scalar_t__ close (int) ; 
 int deflate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ deflateEnd (TYPE_2__*) ; 
 scalar_t__ errno ; 
 scalar_t__ fsync (int) ; 
 scalar_t__ fsync_fname (int /*<<< orphan*/ ,int) ; 
 scalar_t__ fsync_parent_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tar_clear_error () ; 
 scalar_t__ tar_close (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* tar_data ; 
 int /*<<< orphan*/  tar_set_error (char*) ; 
 int /*<<< orphan*/  tar_write_compressed_data (char*,int,int) ; 
 size_t write (int,char*,size_t) ; 

__attribute__((used)) static bool
tar_finish(void)
{
	char		zerobuf[1024];

	tar_clear_error();

	if (tar_data->currentfile)
	{
		if (tar_close(tar_data->currentfile, CLOSE_NORMAL) != 0)
			return false;
	}

	/* A tarfile always ends with two empty blocks */
	MemSet(zerobuf, 0, sizeof(zerobuf));
	if (!tar_data->compression)
	{
		errno = 0;
		if (write(tar_data->fd, zerobuf, sizeof(zerobuf)) != sizeof(zerobuf))
		{
			/* if write didn't set errno, assume problem is no disk space */
			if (errno == 0)
				errno = ENOSPC;
			return false;
		}
	}
#ifdef HAVE_LIBZ
	else
	{
		if (!tar_write_compressed_data(zerobuf, sizeof(zerobuf), false))
			return false;

		/* Also flush all data to make sure the gzip stream is finished */
		tar_data->zp->next_in = NULL;
		tar_data->zp->avail_in = 0;
		while (true)
		{
			int			r;

			r = deflate(tar_data->zp, Z_FINISH);

			if (r == Z_STREAM_ERROR)
			{
				tar_set_error("could not compress data");
				return false;
			}
			if (tar_data->zp->avail_out < ZLIB_OUT_SIZE)
			{
				size_t		len = ZLIB_OUT_SIZE - tar_data->zp->avail_out;

				errno = 0;
				if (write(tar_data->fd, tar_data->zlibOut, len) != len)
				{
					/*
					 * If write didn't set errno, assume problem is no disk
					 * space.
					 */
					if (errno == 0)
						errno = ENOSPC;
					return false;
				}
			}
			if (r == Z_STREAM_END)
				break;
		}

		if (deflateEnd(tar_data->zp) != Z_OK)
		{
			tar_set_error("could not close compression stream");
			return false;
		}
	}
#endif

	/* sync the empty blocks as well, since they're after the last file */
	if (tar_data->sync)
	{
		if (fsync(tar_data->fd) != 0)
			return false;
	}

	if (close(tar_data->fd) != 0)
		return false;

	tar_data->fd = -1;

	if (tar_data->sync)
	{
		if (fsync_fname(tar_data->tarfilename, false) != 0)
			return false;
		if (fsync_parent_path(tar_data->tarfilename) != 0)
			return false;
	}

	return true;
}