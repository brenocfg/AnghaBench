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
typedef  int /*<<< orphan*/  xfs_fsize_t ;
struct xfs_trans {int dummy; } ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int xfs_itruncate_extents_flags (struct xfs_trans**,struct xfs_inode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
xfs_itruncate_extents(
	struct xfs_trans	**tpp,
	struct xfs_inode	*ip,
	int			whichfork,
	xfs_fsize_t		new_size)
{
	return xfs_itruncate_extents_flags(tpp, ip, whichfork, new_size, 0);
}