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
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct z_erofs_pcluster {TYPE_1__ obj; } ;
struct z_erofs_collection {int /*<<< orphan*/  vcnt; int /*<<< orphan*/  nr_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct z_erofs_collection* z_erofs_primarycollection (struct z_erofs_pcluster*) ; 

__attribute__((used)) static void z_erofs_pcluster_init_always(struct z_erofs_pcluster *pcl)
{
	struct z_erofs_collection *cl = z_erofs_primarycollection(pcl);

	atomic_set(&pcl->obj.refcount, 1);

	DBG_BUGON(cl->nr_pages);
	DBG_BUGON(cl->vcnt);
}