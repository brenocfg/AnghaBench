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
struct z_erofs_collector {int cl; scalar_t__ owned_head; scalar_t__ mode; int /*<<< orphan*/  compressedpages; TYPE_1__* pcl; int /*<<< orphan*/  vector; } ;
struct z_erofs_collection {int /*<<< orphan*/  vcnt; int /*<<< orphan*/  pagevec; } ;
struct inode {int dummy; } ;
struct erofs_map_blocks {int /*<<< orphan*/  m_pa; } ;
struct TYPE_2__ {int /*<<< orphan*/  compressed_pages; } ;

/* Variables and functions */
 scalar_t__ COLLECT_PRIMARY ; 
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int EINVAL ; 
 struct z_erofs_collection* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct z_erofs_collection*) ; 
 int /*<<< orphan*/  PAGE_ALIGNED (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct z_erofs_collection*) ; 
 scalar_t__ Z_EROFS_CLUSTER_MAX_PAGES ; 
 int /*<<< orphan*/  Z_EROFS_NR_INLINE_PAGEVECS ; 
 scalar_t__ Z_EROFS_PCLUSTER_NIL ; 
 scalar_t__ Z_EROFS_PCLUSTER_TAIL_CLOSED ; 
 struct z_erofs_collection* cllookup (struct z_erofs_collector*,struct inode*,struct erofs_map_blocks*) ; 
 struct z_erofs_collection* clregister (struct z_erofs_collector*,struct inode*,struct erofs_map_blocks*) ; 
 int /*<<< orphan*/  z_erofs_pagevec_ctor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int z_erofs_collector_begin(struct z_erofs_collector *clt,
				   struct inode *inode,
				   struct erofs_map_blocks *map)
{
	struct z_erofs_collection *cl;

	DBG_BUGON(clt->cl);

	/* must be Z_EROFS_PCLUSTER_TAIL or pointed to previous collection */
	DBG_BUGON(clt->owned_head == Z_EROFS_PCLUSTER_NIL);
	DBG_BUGON(clt->owned_head == Z_EROFS_PCLUSTER_TAIL_CLOSED);

	if (!PAGE_ALIGNED(map->m_pa)) {
		DBG_BUGON(1);
		return -EINVAL;
	}

repeat:
	cl = cllookup(clt, inode, map);
	if (!cl) {
		cl = clregister(clt, inode, map);

		if (cl == ERR_PTR(-EAGAIN))
			goto repeat;
	}

	if (IS_ERR(cl))
		return PTR_ERR(cl);

	z_erofs_pagevec_ctor_init(&clt->vector, Z_EROFS_NR_INLINE_PAGEVECS,
				  cl->pagevec, cl->vcnt);

	clt->compressedpages = clt->pcl->compressed_pages;
	if (clt->mode <= COLLECT_PRIMARY) /* cannot do in-place I/O */
		clt->compressedpages += Z_EROFS_CLUSTER_MAX_PAGES;
	return 0;
}