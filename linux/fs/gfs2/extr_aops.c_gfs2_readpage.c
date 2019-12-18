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
struct page {struct address_space* mapping; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct file {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int AOP_TRUNCATED_PAGE ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int __gfs2_readpage (struct file*,struct page*) ; 
 int /*<<< orphan*/  gfs2_glock_dq (struct gfs2_holder*) ; 
 int gfs2_glock_nq (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int gfs2_readpage(struct file *file, struct page *page)
{
	struct address_space *mapping = page->mapping;
	struct gfs2_inode *ip = GFS2_I(mapping->host);
	struct gfs2_holder gh;
	int error;

	unlock_page(page);
	gfs2_holder_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
	error = gfs2_glock_nq(&gh);
	if (unlikely(error))
		goto out;
	error = AOP_TRUNCATED_PAGE;
	lock_page(page);
	if (page->mapping == mapping && !PageUptodate(page))
		error = __gfs2_readpage(file, page);
	else
		unlock_page(page);
	gfs2_glock_dq(&gh);
out:
	gfs2_holder_uninit(&gh);
	if (error && error != AOP_TRUNCATED_PAGE)
		lock_page(page);
	return error;
}