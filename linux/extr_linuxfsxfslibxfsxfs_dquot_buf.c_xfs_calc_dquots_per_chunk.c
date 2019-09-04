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
typedef  int /*<<< orphan*/  xfs_dqblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BBTOB (unsigned int) ; 

int
xfs_calc_dquots_per_chunk(
	unsigned int		nbblks)	/* basic block units */
{
	ASSERT(nbblks > 0);
	return BBTOB(nbblks) / sizeof(xfs_dqblk_t);
}