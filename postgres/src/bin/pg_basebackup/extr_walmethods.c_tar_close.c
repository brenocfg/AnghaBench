#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  int /*<<< orphan*/ * Walfile ;
typedef  scalar_t__ WalCloseMethod ;
struct TYPE_8__ {scalar_t__ ofs_start; size_t pad_to_size; size_t currpos; struct TYPE_8__* pathname; int /*<<< orphan*/ * header; } ;
typedef  TYPE_2__ TarMethodFile ;
struct TYPE_9__ {TYPE_1__* currentfile; int /*<<< orphan*/  fd; scalar_t__ compression; int /*<<< orphan*/  zp; } ;
struct TYPE_7__ {int /*<<< orphan*/ * header; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ CLOSE_NORMAL ; 
 scalar_t__ CLOSE_UNLINK ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOSPC ; 
 int /*<<< orphan*/  MemSet (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ Z_OK ; 
 scalar_t__ deflateParams (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ ftruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_free (TYPE_2__*) ; 
 int /*<<< orphan*/  print_tar_number (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int tarChecksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tar_clear_error () ; 
 TYPE_4__* tar_data ; 
 int tar_get_current_pos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tar_set_error (char*) ; 
 scalar_t__ tar_sync (int /*<<< orphan*/ *) ; 
 int tar_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  tar_write_compressed_data (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  tar_write_padding_data (TYPE_2__*,size_t) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
tar_close(Walfile f, WalCloseMethod method)
{
	ssize_t		filesize;
	int			padding;
	TarMethodFile *tf = (TarMethodFile *) f;

	Assert(f != NULL);
	tar_clear_error();

	if (method == CLOSE_UNLINK)
	{
		if (tar_data->compression)
		{
			tar_set_error("unlink not supported with compression");
			return -1;
		}

		/*
		 * Unlink the file that we just wrote to the tar. We do this by
		 * truncating it to the start of the header. This is safe as we only
		 * allow writing of the very last file.
		 */
		if (ftruncate(tar_data->fd, tf->ofs_start) != 0)
			return -1;

		pg_free(tf->pathname);
		pg_free(tf);
		tar_data->currentfile = NULL;

		return 0;
	}

	/*
	 * Pad the file itself with zeroes if necessary. Note that this is
	 * different from the tar format padding -- this is the padding we asked
	 * for when the file was opened.
	 */
	if (tf->pad_to_size)
	{
		if (tar_data->compression)
		{
			/*
			 * A compressed tarfile is padded on close since we cannot know
			 * the size of the compressed output until the end.
			 */
			size_t		sizeleft = tf->pad_to_size - tf->currpos;

			if (sizeleft)
			{
				if (!tar_write_padding_data(tf, sizeleft))
					return -1;
			}
		}
		else
		{
			/*
			 * An uncompressed tarfile was padded on creation, so just adjust
			 * the current position as if we seeked to the end.
			 */
			tf->currpos = tf->pad_to_size;
		}
	}

	/*
	 * Get the size of the file, and pad the current data up to the nearest
	 * 512 byte boundary.
	 */
	filesize = tar_get_current_pos(f);
	padding = ((filesize + 511) & ~511) - filesize;
	if (padding)
	{
		char		zerobuf[512];

		MemSet(zerobuf, 0, padding);
		if (tar_write(f, zerobuf, padding) != padding)
			return -1;
	}


#ifdef HAVE_LIBZ
	if (tar_data->compression)
	{
		/* Flush the current buffer */
		if (!tar_write_compressed_data(NULL, 0, true))
		{
			errno = EINVAL;
			return -1;
		}
	}
#endif

	/*
	 * Now go back and update the header with the correct filesize and
	 * possibly also renaming the file. We overwrite the entire current header
	 * when done, including the checksum.
	 */
	print_tar_number(&(tf->header[124]), 12, filesize);

	if (method == CLOSE_NORMAL)

		/*
		 * We overwrite it with what it was before if we have no tempname,
		 * since we're going to write the buffer anyway.
		 */
		strlcpy(&(tf->header[0]), tf->pathname, 100);

	print_tar_number(&(tf->header[148]), 8, tarChecksum(((TarMethodFile *) f)->header));
	if (lseek(tar_data->fd, tf->ofs_start, SEEK_SET) != ((TarMethodFile *) f)->ofs_start)
		return -1;
	if (!tar_data->compression)
	{
		errno = 0;
		if (write(tar_data->fd, tf->header, 512) != 512)
		{
			/* if write didn't set errno, assume problem is no disk space */
			if (errno == 0)
				errno = ENOSPC;
			return -1;
		}
	}
#ifdef HAVE_LIBZ
	else
	{
		/* Turn off compression */
		if (deflateParams(tar_data->zp, 0, 0) != Z_OK)
		{
			tar_set_error("could not change compression parameters");
			return -1;
		}

		/* Overwrite the header, assuming the size will be the same */
		if (!tar_write_compressed_data(tar_data->currentfile->header, 512, true))
			return -1;

		/* Turn compression back on */
		if (deflateParams(tar_data->zp, tar_data->compression, 0) != Z_OK)
		{
			tar_set_error("could not change compression parameters");
			return -1;
		}
	}
#endif

	/* Move file pointer back down to end, so we can write the next file */
	if (lseek(tar_data->fd, 0, SEEK_END) < 0)
		return -1;

	/* Always fsync on close, so the padding gets fsynced */
	if (tar_sync(f) < 0)
		exit(1);

	/* Clean up and done */
	pg_free(tf->pathname);
	pg_free(tf);
	tar_data->currentfile = NULL;

	return 0;
}