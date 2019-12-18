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
struct TYPE_2__ {int /*<<< orphan*/  blkaddr; int /*<<< orphan*/ * delta; } ;
struct z_erofs_vle_decompressed_index {TYPE_1__ di_u; int /*<<< orphan*/  di_clusterofs; int /*<<< orphan*/  di_advise; } ;
struct z_erofs_maprecorder {unsigned long lcn; int clusterofs; unsigned int type; int /*<<< orphan*/  pblk; void** delta; struct z_erofs_vle_decompressed_index* kaddr; struct inode* inode; } ;
struct inode {int dummy; } ;
struct erofs_inode {int z_logical_clusterbits; scalar_t__ const xattr_isize; scalar_t__ const inode_isize; int /*<<< orphan*/  nid; } ;
typedef  scalar_t__ erofs_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int EOPNOTSUPP ; 
 struct erofs_inode* EROFS_I (struct inode* const) ; 
 int /*<<< orphan*/  EROFS_I_SB (struct inode* const) ; 
#define  Z_EROFS_VLE_CLUSTER_TYPE_HEAD 130 
#define  Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD 129 
#define  Z_EROFS_VLE_CLUSTER_TYPE_PLAIN 128 
 unsigned int Z_EROFS_VLE_DI_CLUSTER_TYPE_BIT ; 
 int Z_EROFS_VLE_DI_CLUSTER_TYPE_BITS ; 
 scalar_t__ Z_EROFS_VLE_LEGACY_INDEX_ALIGN (scalar_t__ const) ; 
 int /*<<< orphan*/  erofs_blknr (scalar_t__ const) ; 
 int erofs_blkoff (scalar_t__ const) ; 
 scalar_t__ iloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int z_erofs_reload_indexes (struct z_erofs_maprecorder*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vle_legacy_load_cluster_from_disk(struct z_erofs_maprecorder *m,
					     unsigned long lcn)
{
	struct inode *const inode = m->inode;
	struct erofs_inode *const vi = EROFS_I(inode);
	const erofs_off_t ibase = iloc(EROFS_I_SB(inode), vi->nid);
	const erofs_off_t pos =
		Z_EROFS_VLE_LEGACY_INDEX_ALIGN(ibase + vi->inode_isize +
					       vi->xattr_isize) +
		lcn * sizeof(struct z_erofs_vle_decompressed_index);
	struct z_erofs_vle_decompressed_index *di;
	unsigned int advise, type;
	int err;

	err = z_erofs_reload_indexes(m, erofs_blknr(pos));
	if (err)
		return err;

	m->lcn = lcn;
	di = m->kaddr + erofs_blkoff(pos);

	advise = le16_to_cpu(di->di_advise);
	type = (advise >> Z_EROFS_VLE_DI_CLUSTER_TYPE_BIT) &
		((1 << Z_EROFS_VLE_DI_CLUSTER_TYPE_BITS) - 1);
	switch (type) {
	case Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD:
		m->clusterofs = 1 << vi->z_logical_clusterbits;
		m->delta[0] = le16_to_cpu(di->di_u.delta[0]);
		m->delta[1] = le16_to_cpu(di->di_u.delta[1]);
		break;
	case Z_EROFS_VLE_CLUSTER_TYPE_PLAIN:
	case Z_EROFS_VLE_CLUSTER_TYPE_HEAD:
		m->clusterofs = le16_to_cpu(di->di_clusterofs);
		m->pblk = le32_to_cpu(di->di_u.blkaddr);
		break;
	default:
		DBG_BUGON(1);
		return -EOPNOTSUPP;
	}
	m->type = type;
	return 0;
}