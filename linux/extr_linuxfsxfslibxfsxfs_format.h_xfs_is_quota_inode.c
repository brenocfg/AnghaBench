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
typedef  scalar_t__ xfs_ino_t ;
struct xfs_sb {scalar_t__ sb_uquotino; scalar_t__ sb_gquotino; scalar_t__ sb_pquotino; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
xfs_is_quota_inode(struct xfs_sb *sbp, xfs_ino_t ino)
{
	return (ino == sbp->sb_uquotino ||
		ino == sbp->sb_gquotino ||
		ino == sbp->sb_pquotino);
}