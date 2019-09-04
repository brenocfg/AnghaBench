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
struct virtio_balloon {int /*<<< orphan*/  vdev; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  __virtio32 ;

/* Variables and functions */
 unsigned int VIRTIO_BALLOON_PAGES_PER_PAGE ; 
 int /*<<< orphan*/  cpu_to_virtio32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ page_to_balloon_pfn (struct page*) ; 

__attribute__((used)) static void set_page_pfns(struct virtio_balloon *vb,
			  __virtio32 pfns[], struct page *page)
{
	unsigned int i;

	/*
	 * Set balloon pfns pointing at this page.
	 * Note that the first pfn points at start of the page.
	 */
	for (i = 0; i < VIRTIO_BALLOON_PAGES_PER_PAGE; i++)
		pfns[i] = cpu_to_virtio32(vb->vdev,
					  page_to_balloon_pfn(page) + i);
}