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
struct z_erofs_pcluster {int /*<<< orphan*/ ** compressed_pages; } ;
struct z_erofs_collection {scalar_t__ vcnt; scalar_t__ nr_pages; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int Z_EROFS_CLUSTER_MAX_PAGES ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct z_erofs_collection* z_erofs_primarycollection (struct z_erofs_pcluster*) ; 

__attribute__((used)) static void z_erofs_pcluster_init_once(void *ptr)
{
	struct z_erofs_pcluster *pcl = ptr;
	struct z_erofs_collection *cl = z_erofs_primarycollection(pcl);
	unsigned int i;

	mutex_init(&cl->lock);
	cl->nr_pages = 0;
	cl->vcnt = 0;
	for (i = 0; i < Z_EROFS_CLUSTER_MAX_PAGES; ++i)
		pcl->compressed_pages[i] = NULL;
}