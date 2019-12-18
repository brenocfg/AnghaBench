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
struct nfs_commit_info {int /*<<< orphan*/  dreq; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  wb; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_DIRTY_DATASYNC ; 
 int /*<<< orphan*/  NR_UNSTABLE_NFS ; 
 int /*<<< orphan*/  WB_RECLAIMABLE ; 
 int /*<<< orphan*/  __mark_inode_dirty (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_wb_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* inode_to_bdi (struct inode*) ; 
 TYPE_1__* page_file_mapping (struct page*) ; 

__attribute__((used)) static inline
void nfs_mark_page_unstable(struct page *page, struct nfs_commit_info *cinfo)
{
	if (!cinfo->dreq) {
		struct inode *inode = page_file_mapping(page)->host;

		inc_node_page_state(page, NR_UNSTABLE_NFS);
		inc_wb_stat(&inode_to_bdi(inode)->wb, WB_RECLAIMABLE);
		__mark_inode_dirty(inode, I_DIRTY_DATASYNC);
	}
}