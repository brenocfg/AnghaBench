#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfs_inode {TYPE_1__* i_mount; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_sb; scalar_t__ m_always_cow; } ;

/* Variables and functions */
 scalar_t__ xfs_sb_version_hasreflink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool xfs_is_always_cow_inode(struct xfs_inode *ip)
{
	return ip->i_mount->m_always_cow &&
		xfs_sb_version_hasreflink(&ip->i_mount->m_sb);
}