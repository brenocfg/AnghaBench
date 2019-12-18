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
struct gfs2_log_header_host {int dummy; } ;
struct gfs2_jdesc {TYPE_1__* jd_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 scalar_t__ PageError (struct page*) ; 
 struct page* find_get_page (int /*<<< orphan*/ ,unsigned long) ; 
 int gfs2_jhead_pg_srch (struct gfs2_jdesc*,struct gfs2_log_header_host*,struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_locked (struct page*) ; 

__attribute__((used)) static void gfs2_jhead_process_page(struct gfs2_jdesc *jd, unsigned long index,
				    struct gfs2_log_header_host *head,
				    bool *done)
{
	struct page *page;

	page = find_get_page(jd->jd_inode->i_mapping, index);
	wait_on_page_locked(page);

	if (PageError(page))
		*done = true;

	if (!*done)
		*done = gfs2_jhead_pg_srch(jd, head, page);

	put_page(page); /* Once for find_get_page */
	put_page(page); /* Once more for find_or_create_page */
}