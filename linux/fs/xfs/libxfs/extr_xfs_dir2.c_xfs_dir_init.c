#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  t_mountp; } ;
typedef  TYPE_2__ xfs_trans_t ;
struct TYPE_11__ {int /*<<< orphan*/  i_ino; TYPE_1__* i_mount; } ;
typedef  TYPE_3__ xfs_inode_t ;
struct xfs_da_args {TYPE_2__* trans; TYPE_3__* dp; int /*<<< orphan*/  geo; } ;
struct TYPE_12__ {int /*<<< orphan*/  i_mode; } ;
struct TYPE_9__ {int /*<<< orphan*/  m_dir_geo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_7__* VFS_I (TYPE_3__*) ; 
 int /*<<< orphan*/  kmem_free (struct xfs_da_args*) ; 
 struct xfs_da_args* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int xfs_dir2_sf_create (struct xfs_da_args*,int /*<<< orphan*/ ) ; 
 int xfs_dir_ino_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_dir_init(
	xfs_trans_t	*tp,
	xfs_inode_t	*dp,
	xfs_inode_t	*pdp)
{
	struct xfs_da_args *args;
	int		error;

	ASSERT(S_ISDIR(VFS_I(dp)->i_mode));
	error = xfs_dir_ino_validate(tp->t_mountp, pdp->i_ino);
	if (error)
		return error;

	args = kmem_zalloc(sizeof(*args), KM_NOFS);
	if (!args)
		return -ENOMEM;

	args->geo = dp->i_mount->m_dir_geo;
	args->dp = dp;
	args->trans = tp;
	error = xfs_dir2_sf_create(args, pdp->i_ino);
	kmem_free(args);
	return error;
}