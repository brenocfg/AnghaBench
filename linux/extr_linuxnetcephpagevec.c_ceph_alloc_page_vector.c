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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct page** ERR_PTR (int /*<<< orphan*/ ) ; 
 struct page* __page_cache_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_release_page_vector (struct page**,int) ; 
 struct page** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

struct page **ceph_alloc_page_vector(int num_pages, gfp_t flags)
{
	struct page **pages;
	int i;

	pages = kmalloc_array(num_pages, sizeof(*pages), flags);
	if (!pages)
		return ERR_PTR(-ENOMEM);
	for (i = 0; i < num_pages; i++) {
		pages[i] = __page_cache_alloc(flags);
		if (pages[i] == NULL) {
			ceph_release_page_vector(pages, i);
			return ERR_PTR(-ENOMEM);
		}
	}
	return pages;
}