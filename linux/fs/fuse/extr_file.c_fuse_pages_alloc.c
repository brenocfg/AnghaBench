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
struct fuse_page_desc {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct page** kzalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page **fuse_pages_alloc(unsigned int npages, gfp_t flags,
				      struct fuse_page_desc **desc)
{
	struct page **pages;

	pages = kzalloc(npages * (sizeof(struct page *) +
				  sizeof(struct fuse_page_desc)), flags);
	*desc = (void *) (pages + npages);

	return pages;
}