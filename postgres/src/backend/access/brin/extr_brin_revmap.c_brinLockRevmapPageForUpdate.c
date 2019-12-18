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
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BrinRevmap ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revmap_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Buffer
brinLockRevmapPageForUpdate(BrinRevmap *revmap, BlockNumber heapBlk)
{
	Buffer		rmBuf;

	rmBuf = revmap_get_buffer(revmap, heapBlk);
	LockBuffer(rmBuf, BUFFER_LOCK_EXCLUSIVE);

	return rmBuf;
}