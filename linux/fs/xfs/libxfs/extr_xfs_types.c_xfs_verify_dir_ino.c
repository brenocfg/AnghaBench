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
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 scalar_t__ xfs_internal_inum (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int xfs_verify_ino (struct xfs_mount*,int /*<<< orphan*/ ) ; 

bool
xfs_verify_dir_ino(
	struct xfs_mount	*mp,
	xfs_ino_t		ino)
{
	if (xfs_internal_inum(mp, ino))
		return false;
	return xfs_verify_ino(mp, ino);
}