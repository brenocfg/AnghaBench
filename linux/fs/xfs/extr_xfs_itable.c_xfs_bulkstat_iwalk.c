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
typedef  int /*<<< orphan*/  xfs_ino_t ;
struct xfs_trans {int dummy; } ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int xfs_bulkstat_one_int (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
xfs_bulkstat_iwalk(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	xfs_ino_t		ino,
	void			*data)
{
	int			error;

	error = xfs_bulkstat_one_int(mp, tp, ino, data);
	/* bulkstat just skips over missing inodes */
	if (error == -ENOENT || error == -EINVAL)
		return 0;
	return error;
}