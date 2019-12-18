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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int) ; 
 scalar_t__ P_NEW ; 
 int /*<<< orphan*/  ReleaseAndReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _bt_checkpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Buffer
_bt_relandgetbuf(Relation rel, Buffer obuf, BlockNumber blkno, int access)
{
	Buffer		buf;

	Assert(blkno != P_NEW);
	if (BufferIsValid(obuf))
		LockBuffer(obuf, BUFFER_LOCK_UNLOCK);
	buf = ReleaseAndReadBuffer(obuf, rel, blkno);
	LockBuffer(buf, access);
	_bt_checkpage(rel, buf);
	return buf;
}