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
struct xfs_inode {int dummy; } ;
struct xfs_bulkstat {int /*<<< orphan*/  bs_sick; int /*<<< orphan*/  bs_checked; } ;
struct ioctl_sick_map {int sick_mask; int /*<<< orphan*/  ioctl_mask; } ;

/* Variables and functions */
 struct ioctl_sick_map* ino_map ; 
 int /*<<< orphan*/  xfs_inode_measure_sickness (struct xfs_inode*,unsigned int*,unsigned int*) ; 

void
xfs_bulkstat_health(
	struct xfs_inode		*ip,
	struct xfs_bulkstat		*bs)
{
	const struct ioctl_sick_map	*m;
	unsigned int			sick;
	unsigned int			checked;

	bs->bs_sick = 0;
	bs->bs_checked = 0;

	xfs_inode_measure_sickness(ip, &sick, &checked);
	for (m = ino_map; m->sick_mask; m++) {
		if (checked & m->sick_mask)
			bs->bs_checked |= m->ioctl_mask;
		if (sick & m->sick_mask)
			bs->bs_sick |= m->ioctl_mask;
	}
}