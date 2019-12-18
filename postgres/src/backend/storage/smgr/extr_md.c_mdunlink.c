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
typedef  int /*<<< orphan*/  RelFileNodeBackend ;
typedef  scalar_t__ ForkNumber ;

/* Variables and functions */
 scalar_t__ InvalidForkNumber ; 
 scalar_t__ MAX_FORKNUM ; 
 int /*<<< orphan*/  mdunlinkfork (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
mdunlink(RelFileNodeBackend rnode, ForkNumber forkNum, bool isRedo)
{
	/* Now do the per-fork work */
	if (forkNum == InvalidForkNumber)
	{
		for (forkNum = 0; forkNum <= MAX_FORKNUM; forkNum++)
			mdunlinkfork(rnode, forkNum, isRedo);
	}
	else
		mdunlinkfork(rnode, forkNum, isRedo);
}