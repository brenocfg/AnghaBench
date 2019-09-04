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
struct ocfs2_write_ctxt {int /*<<< orphan*/  w_di_bh; int /*<<< orphan*/  w_unwritten_list; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_write_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_free_unwritten_list (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_unlock_pages (struct ocfs2_write_ctxt*) ; 

__attribute__((used)) static void ocfs2_free_write_ctxt(struct inode *inode,
				  struct ocfs2_write_ctxt *wc)
{
	ocfs2_free_unwritten_list(inode, &wc->w_unwritten_list);
	ocfs2_unlock_pages(wc);
	brelse(wc->w_di_bh);
	kfree(wc);
}