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
struct z_erofs_maprecorder {unsigned long lcn; int type; unsigned int* delta; unsigned long clusterofs; TYPE_1__* inode; struct erofs_map_blocks* map; } ;
struct erofs_map_blocks {unsigned long m_la; int /*<<< orphan*/  m_flags; } ;
struct erofs_inode {unsigned int z_logical_clusterbits; int /*<<< orphan*/  nid; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int EFSCORRUPTED ; 
 int EOPNOTSUPP ; 
 struct erofs_inode* EROFS_I (TYPE_1__*) ; 
 int /*<<< orphan*/  EROFS_MAP_ZIPPED ; 
#define  Z_EROFS_VLE_CLUSTER_TYPE_HEAD 130 
#define  Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD 129 
#define  Z_EROFS_VLE_CLUSTER_TYPE_PLAIN 128 
 int /*<<< orphan*/  erofs_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int vle_load_cluster_from_disk (struct z_erofs_maprecorder*,unsigned long) ; 

__attribute__((used)) static int vle_extent_lookback(struct z_erofs_maprecorder *m,
			       unsigned int lookback_distance)
{
	struct erofs_inode *const vi = EROFS_I(m->inode);
	struct erofs_map_blocks *const map = m->map;
	const unsigned int lclusterbits = vi->z_logical_clusterbits;
	unsigned long lcn = m->lcn;
	int err;

	if (lcn < lookback_distance) {
		erofs_err(m->inode->i_sb,
			  "bogus lookback distance @ nid %llu", vi->nid);
		DBG_BUGON(1);
		return -EFSCORRUPTED;
	}

	/* load extent head logical cluster if needed */
	lcn -= lookback_distance;
	err = vle_load_cluster_from_disk(m, lcn);
	if (err)
		return err;

	switch (m->type) {
	case Z_EROFS_VLE_CLUSTER_TYPE_NONHEAD:
		if (!m->delta[0]) {
			erofs_err(m->inode->i_sb,
				  "invalid lookback distance 0 @ nid %llu",
				  vi->nid);
			DBG_BUGON(1);
			return -EFSCORRUPTED;
		}
		return vle_extent_lookback(m, m->delta[0]);
	case Z_EROFS_VLE_CLUSTER_TYPE_PLAIN:
		map->m_flags &= ~EROFS_MAP_ZIPPED;
		/* fallthrough */
	case Z_EROFS_VLE_CLUSTER_TYPE_HEAD:
		map->m_la = (lcn << lclusterbits) | m->clusterofs;
		break;
	default:
		erofs_err(m->inode->i_sb,
			  "unknown type %u @ lcn %lu of nid %llu",
			  m->type, lcn, vi->nid);
		DBG_BUGON(1);
		return -EOPNOTSUPP;
	}
	return 0;
}