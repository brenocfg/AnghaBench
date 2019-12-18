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
struct page {int dummy; } ;
struct iomap {int dummy; } ;
struct inode {int dummy; } ;
struct gfs2_trans {scalar_t__ tr_num_buf_new; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct gfs2_trans* journal_info; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  I_DIRTY_DATASYNC ; 
 int /*<<< orphan*/  __mark_inode_dirty (struct inode*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  gfs2_is_stuffed (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_page_add_databufs (struct gfs2_inode*,struct page*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfs2_iomap_page_done(struct inode *inode, loff_t pos,
				 unsigned copied, struct page *page,
				 struct iomap *iomap)
{
	struct gfs2_trans *tr = current->journal_info;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);

	if (page && !gfs2_is_stuffed(ip))
		gfs2_page_add_databufs(ip, page, offset_in_page(pos), copied);

	if (tr->tr_num_buf_new)
		__mark_inode_dirty(inode, I_DIRTY_DATASYNC);

	gfs2_trans_end(sdp);
}