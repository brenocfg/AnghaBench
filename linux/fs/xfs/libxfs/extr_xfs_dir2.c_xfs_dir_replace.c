#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_ino_t ;
typedef  int /*<<< orphan*/  xfs_extlen_t ;
struct xfs_trans {int /*<<< orphan*/  t_mountp; } ;
struct xfs_name {int /*<<< orphan*/  type; int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ di_format; } ;
struct xfs_inode {TYPE_3__ i_d; TYPE_2__* i_mount; } ;
struct xfs_da_args {struct xfs_trans* trans; int /*<<< orphan*/  whichfork; int /*<<< orphan*/  total; struct xfs_inode* dp; int /*<<< orphan*/  inumber; int /*<<< orphan*/  hashval; int /*<<< orphan*/  filetype; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  geo; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_mode; } ;
struct TYPE_6__ {TYPE_1__* m_dirnameops; int /*<<< orphan*/  m_dir_geo; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* hashname ) (struct xfs_name*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_4__* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 int /*<<< orphan*/  kmem_free (struct xfs_da_args*) ; 
 struct xfs_da_args* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xfs_name*) ; 
 int xfs_dir2_block_replace (struct xfs_da_args*) ; 
 int xfs_dir2_isblock (struct xfs_da_args*,int*) ; 
 int xfs_dir2_isleaf (struct xfs_da_args*,int*) ; 
 int xfs_dir2_leaf_replace (struct xfs_da_args*) ; 
 int xfs_dir2_node_replace (struct xfs_da_args*) ; 
 int xfs_dir2_sf_replace (struct xfs_da_args*) ; 
 int xfs_dir_ino_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_dir_replace(
	struct xfs_trans	*tp,
	struct xfs_inode	*dp,
	struct xfs_name		*name,		/* name of entry to replace */
	xfs_ino_t		inum,		/* new inode number */
	xfs_extlen_t		total)		/* bmap's total block count */
{
	struct xfs_da_args	*args;
	int			rval;
	int			v;		/* type-checking value */

	ASSERT(S_ISDIR(VFS_I(dp)->i_mode));

	rval = xfs_dir_ino_validate(tp->t_mountp, inum);
	if (rval)
		return rval;

	args = kmem_zalloc(sizeof(*args), KM_NOFS);
	if (!args)
		return -ENOMEM;

	args->geo = dp->i_mount->m_dir_geo;
	args->name = name->name;
	args->namelen = name->len;
	args->filetype = name->type;
	args->hashval = dp->i_mount->m_dirnameops->hashname(name);
	args->inumber = inum;
	args->dp = dp;
	args->total = total;
	args->whichfork = XFS_DATA_FORK;
	args->trans = tp;

	if (dp->i_d.di_format == XFS_DINODE_FMT_LOCAL) {
		rval = xfs_dir2_sf_replace(args);
		goto out_free;
	}

	rval = xfs_dir2_isblock(args, &v);
	if (rval)
		goto out_free;
	if (v) {
		rval = xfs_dir2_block_replace(args);
		goto out_free;
	}

	rval = xfs_dir2_isleaf(args, &v);
	if (rval)
		goto out_free;
	if (v)
		rval = xfs_dir2_leaf_replace(args);
	else
		rval = xfs_dir2_node_replace(args);
out_free:
	kmem_free(args);
	return rval;
}