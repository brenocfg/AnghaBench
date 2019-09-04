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
typedef  size_t u32 ;
struct TYPE_2__ {int /*<<< orphan*/  prev; } ;
struct nfs_pgio_mirror {TYPE_1__ pg_list; } ;
struct nfs_pageio_descriptor {size_t pg_mirror_count; struct nfs_pgio_mirror* pg_mirrors; } ;
struct nfs_page {scalar_t__ wb_index; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 

void nfs_pageio_cond_complete(struct nfs_pageio_descriptor *desc, pgoff_t index)
{
	struct nfs_pgio_mirror *mirror;
	struct nfs_page *prev;
	u32 midx;

	for (midx = 0; midx < desc->pg_mirror_count; midx++) {
		mirror = &desc->pg_mirrors[midx];
		if (!list_empty(&mirror->pg_list)) {
			prev = nfs_list_entry(mirror->pg_list.prev);
			if (index != prev->wb_index + 1) {
				nfs_pageio_complete(desc);
				break;
			}
		}
	}
}