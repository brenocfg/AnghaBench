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
struct nfs4_layoutcommit_args {int /*<<< orphan*/  layoutupdate_page; int /*<<< orphan*/ * layoutupdate_pages; int /*<<< orphan*/  start_p; } ;

/* Variables and functions */
 int DIV_ROUND_UP (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext_tree_free_commitdata(struct nfs4_layoutcommit_args *arg,
		size_t buffer_size)
{
	if (arg->layoutupdate_pages != &arg->layoutupdate_page) {
		int nr_pages = DIV_ROUND_UP(buffer_size, PAGE_SIZE), i;

		for (i = 0; i < nr_pages; i++)
			put_page(arg->layoutupdate_pages[i]);
		vfree(arg->start_p);
		kfree(arg->layoutupdate_pages);
	} else {
		put_page(arg->layoutupdate_page);
	}
}