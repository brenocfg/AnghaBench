#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  temp_blks_read; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {long curOffset; int curFile; int numFiles; scalar_t__ nbytes; TYPE_1__ buffer; int /*<<< orphan*/ * files; } ;
typedef  int /*<<< orphan*/  File ;
typedef  TYPE_2__ BufFile ;

/* Variables and functions */
 scalar_t__ FileRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,long,int /*<<< orphan*/ ) ; 
 long MAX_PHYSICAL_FILESIZE ; 
 int /*<<< orphan*/  WAIT_EVENT_BUFFILE_READ ; 
 TYPE_3__ pgBufferUsage ; 

__attribute__((used)) static void
BufFileLoadBuffer(BufFile *file)
{
	File		thisfile;

	/*
	 * Advance to next component file if necessary and possible.
	 */
	if (file->curOffset >= MAX_PHYSICAL_FILESIZE &&
		file->curFile + 1 < file->numFiles)
	{
		file->curFile++;
		file->curOffset = 0L;
	}

	/*
	 * Read whatever we can get, up to a full bufferload.
	 */
	thisfile = file->files[file->curFile];
	file->nbytes = FileRead(thisfile,
							file->buffer.data,
							sizeof(file->buffer),
							file->curOffset,
							WAIT_EVENT_BUFFILE_READ);
	if (file->nbytes < 0)
		file->nbytes = 0;
	/* we choose not to advance curOffset here */

	if (file->nbytes > 0)
		pgBufferUsage.temp_blks_read++;
}