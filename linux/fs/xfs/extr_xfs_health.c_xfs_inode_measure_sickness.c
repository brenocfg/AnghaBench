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
struct xfs_inode {unsigned int i_sick; unsigned int i_checked; int /*<<< orphan*/  i_flags_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
xfs_inode_measure_sickness(
	struct xfs_inode	*ip,
	unsigned int		*sick,
	unsigned int		*checked)
{
	spin_lock(&ip->i_flags_lock);
	*sick = ip->i_sick;
	*checked = ip->i_checked;
	spin_unlock(&ip->i_flags_lock);
}