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
struct afs_vnode {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void afs_get_inode_cache(struct afs_vnode *vnode)
{
#ifdef CONFIG_AFS_FSCACHE
	struct {
		u32 vnode_id;
		u32 unique;
		u32 vnode_id_ext[2];	/* Allow for a 96-bit key */
	} __packed key;
	struct afs_vnode_cache_aux aux;

	if (vnode->status.type == AFS_FTYPE_DIR) {
		vnode->cache = NULL;
		return;
	}

	key.vnode_id		= vnode->fid.vnode;
	key.unique		= vnode->fid.unique;
	key.vnode_id_ext[0]	= 0;
	key.vnode_id_ext[1]	= 0;
	aux.data_version	= vnode->status.data_version;

	vnode->cache = fscache_acquire_cookie(vnode->volume->cache,
					      &afs_vnode_cache_index_def,
					      &key, sizeof(key),
					      &aux, sizeof(aux),
					      vnode, vnode->status.size, true);
#endif
}