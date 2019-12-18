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
struct page {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  wb; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_UNSTABLE_NFS ; 
 int /*<<< orphan*/  WB_RECLAIMABLE ; 
 int /*<<< orphan*/  dec_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_wb_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* inode_to_bdi (int /*<<< orphan*/ ) ; 
 TYPE_1__* page_file_mapping (struct page*) ; 

__attribute__((used)) static void
nfs_clear_page_commit(struct page *page)
{
	dec_node_page_state(page, NR_UNSTABLE_NFS);
	dec_wb_stat(&inode_to_bdi(page_file_mapping(page)->host)->wb,
		    WB_RECLAIMABLE);
}