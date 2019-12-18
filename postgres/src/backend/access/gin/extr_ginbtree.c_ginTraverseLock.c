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
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int GIN_EXCLUSIVE ; 
 int GIN_SHARE ; 
 int GIN_UNLOCK ; 
 scalar_t__ GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int) ; 

int
ginTraverseLock(Buffer buffer, bool searchMode)
{
	Page		page;
	int			access = GIN_SHARE;

	LockBuffer(buffer, GIN_SHARE);
	page = BufferGetPage(buffer);
	if (GinPageIsLeaf(page))
	{
		if (searchMode == false)
		{
			/* we should relock our page */
			LockBuffer(buffer, GIN_UNLOCK);
			LockBuffer(buffer, GIN_EXCLUSIVE);

			/* But root can become non-leaf during relock */
			if (!GinPageIsLeaf(page))
			{
				/* restore old lock type (very rare) */
				LockBuffer(buffer, GIN_UNLOCK);
				LockBuffer(buffer, GIN_SHARE);
			}
			else
				access = GIN_EXCLUSIVE;
		}
	}

	return access;
}