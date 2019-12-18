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
struct fuse_args_pages {unsigned int num_pages; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty_lock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fuse_release_user_pages(struct fuse_args_pages *ap,
				    bool should_dirty)
{
	unsigned int i;

	for (i = 0; i < ap->num_pages; i++) {
		if (should_dirty)
			set_page_dirty_lock(ap->pages[i]);
		put_page(ap->pages[i]);
	}
}