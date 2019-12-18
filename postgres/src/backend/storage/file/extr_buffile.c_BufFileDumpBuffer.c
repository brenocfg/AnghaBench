#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
struct TYPE_8__ {int /*<<< orphan*/  temp_blks_written; } ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_7__ {int nbytes; scalar_t__ curOffset; scalar_t__ curFile; scalar_t__ numFiles; int dirty; scalar_t__ pos; TYPE_1__ buffer; int /*<<< orphan*/ * files; } ;
typedef  int /*<<< orphan*/  File ;
typedef  TYPE_2__ BufFile ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int FileWrite (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_PHYSICAL_FILESIZE ; 
 int /*<<< orphan*/  WAIT_EVENT_BUFFILE_WRITE ; 
 int /*<<< orphan*/  extendBufFile (TYPE_2__*) ; 
 TYPE_3__ pgBufferUsage ; 

__attribute__((used)) static void
BufFileDumpBuffer(BufFile *file)
{
	int			wpos = 0;
	int			bytestowrite;
	File		thisfile;

	/*
	 * Unlike BufFileLoadBuffer, we must dump the whole buffer even if it
	 * crosses a component-file boundary; so we need a loop.
	 */
	while (wpos < file->nbytes)
	{
		off_t		availbytes;

		/*
		 * Advance to next component file if necessary and possible.
		 */
		if (file->curOffset >= MAX_PHYSICAL_FILESIZE)
		{
			while (file->curFile + 1 >= file->numFiles)
				extendBufFile(file);
			file->curFile++;
			file->curOffset = 0L;
		}

		/*
		 * Determine how much we need to write into this file.
		 */
		bytestowrite = file->nbytes - wpos;
		availbytes = MAX_PHYSICAL_FILESIZE - file->curOffset;

		if ((off_t) bytestowrite > availbytes)
			bytestowrite = (int) availbytes;

		thisfile = file->files[file->curFile];
		bytestowrite = FileWrite(thisfile,
								 file->buffer.data + wpos,
								 bytestowrite,
								 file->curOffset,
								 WAIT_EVENT_BUFFILE_WRITE);
		if (bytestowrite <= 0)
			return;				/* failed to write */
		file->curOffset += bytestowrite;
		wpos += bytestowrite;

		pgBufferUsage.temp_blks_written++;
	}
	file->dirty = false;

	/*
	 * At this point, curOffset has been advanced to the end of the buffer,
	 * ie, its original value + nbytes.  We need to make it point to the
	 * logical file position, ie, original value + pos, in case that is less
	 * (as could happen due to a small backwards seek in a dirty buffer!)
	 */
	file->curOffset -= (file->nbytes - file->pos);
	if (file->curOffset < 0)	/* handle possible segment crossing */
	{
		file->curFile--;
		Assert(file->curFile >= 0);
		file->curOffset += MAX_PHYSICAL_FILESIZE;
	}

	/*
	 * Now we can set the buffer empty without changing the logical position
	 */
	file->pos = 0;
	file->nbytes = 0;
}