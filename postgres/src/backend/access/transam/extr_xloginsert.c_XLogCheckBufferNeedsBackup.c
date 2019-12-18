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
typedef  scalar_t__ XLogRecPtr ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFullPageWriteInfo (scalar_t__*,int*) ; 
 scalar_t__ PageGetLSN (int /*<<< orphan*/ ) ; 

bool
XLogCheckBufferNeedsBackup(Buffer buffer)
{
	XLogRecPtr	RedoRecPtr;
	bool		doPageWrites;
	Page		page;

	GetFullPageWriteInfo(&RedoRecPtr, &doPageWrites);

	page = BufferGetPage(buffer);

	if (doPageWrites && PageGetLSN(page) <= RedoRecPtr)
		return true;			/* buffer requires backup */

	return false;				/* buffer does not need to be backed up */
}