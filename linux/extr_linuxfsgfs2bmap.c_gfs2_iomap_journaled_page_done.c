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
struct page {int dummy; } ;
struct iomap {int dummy; } ;
struct inode {int dummy; } ;
struct gfs2_inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  gfs2_page_add_databufs (struct gfs2_inode*,struct page*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfs2_iomap_journaled_page_done(struct inode *inode, loff_t pos,
				unsigned copied, struct page *page,
				struct iomap *iomap)
{
	struct gfs2_inode *ip = GFS2_I(inode);

	gfs2_page_add_databufs(ip, page, offset_in_page(pos), copied);
}