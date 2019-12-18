#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int index; } ;
struct z_erofs_pcluster {int length; int clusterbits; int /*<<< orphan*/ *** next; TYPE_1__ obj; int /*<<< orphan*/  algorithmformat; } ;
struct z_erofs_collector {struct z_erofs_collection* cl; struct z_erofs_pcluster* pcl; int /*<<< orphan*/ **** owned_head; struct z_erofs_pcluster* tailpcl; int /*<<< orphan*/  mode; } ;
struct z_erofs_collection {int pageofs; int /*<<< orphan*/  lock; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct erofs_map_blocks {int m_pa; int m_llen; int m_flags; int m_la; } ;
struct TYPE_4__ {int* z_physical_clusterbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLLECT_PRIMARY_FOLLOWED ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* EROFS_I (struct inode*) ; 
 int EROFS_MAP_FULL_MAPPED ; 
 int EROFS_MAP_ZIPPED ; 
 struct z_erofs_collection* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  Z_EROFS_COMPRESSION_LZ4 ; 
 int /*<<< orphan*/  Z_EROFS_COMPRESSION_SHIFTED ; 
 int Z_EROFS_PCLUSTER_FULL_LENGTH ; 
 int Z_EROFS_PCLUSTER_LENGTH_BIT ; 
 int /*<<< orphan*/ ** Z_EROFS_PCLUSTER_TAIL ; 
 int erofs_register_workgroup (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct z_erofs_pcluster* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct z_erofs_pcluster*) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcluster_cachep ; 
 int /*<<< orphan*/  z_erofs_pcluster_init_always (struct z_erofs_pcluster*) ; 
 struct z_erofs_collection* z_erofs_primarycollection (struct z_erofs_pcluster*) ; 

__attribute__((used)) static struct z_erofs_collection *clregister(struct z_erofs_collector *clt,
					     struct inode *inode,
					     struct erofs_map_blocks *map)
{
	struct z_erofs_pcluster *pcl;
	struct z_erofs_collection *cl;
	int err;

	/* no available workgroup, let's allocate one */
	pcl = kmem_cache_alloc(pcluster_cachep, GFP_NOFS);
	if (!pcl)
		return ERR_PTR(-ENOMEM);

	z_erofs_pcluster_init_always(pcl);
	pcl->obj.index = map->m_pa >> PAGE_SHIFT;

	pcl->length = (map->m_llen << Z_EROFS_PCLUSTER_LENGTH_BIT) |
		(map->m_flags & EROFS_MAP_FULL_MAPPED ?
			Z_EROFS_PCLUSTER_FULL_LENGTH : 0);

	if (map->m_flags & EROFS_MAP_ZIPPED)
		pcl->algorithmformat = Z_EROFS_COMPRESSION_LZ4;
	else
		pcl->algorithmformat = Z_EROFS_COMPRESSION_SHIFTED;

	pcl->clusterbits = EROFS_I(inode)->z_physical_clusterbits[0];
	pcl->clusterbits -= PAGE_SHIFT;

	/* new pclusters should be claimed as type 1, primary and followed */
	pcl->next = clt->owned_head;
	clt->mode = COLLECT_PRIMARY_FOLLOWED;

	cl = z_erofs_primarycollection(pcl);
	cl->pageofs = map->m_la & ~PAGE_MASK;

	/*
	 * lock all primary followed works before visible to others
	 * and mutex_trylock *never* fails for a new pcluster.
	 */
	mutex_trylock(&cl->lock);

	err = erofs_register_workgroup(inode->i_sb, &pcl->obj, 0);
	if (err) {
		mutex_unlock(&cl->lock);
		kmem_cache_free(pcluster_cachep, pcl);
		return ERR_PTR(-EAGAIN);
	}
	/* used to check tail merging loop due to corrupted images */
	if (clt->owned_head == Z_EROFS_PCLUSTER_TAIL)
		clt->tailpcl = pcl;
	clt->owned_head = &pcl->next;
	clt->pcl = pcl;
	clt->cl = cl;
	return cl;
}