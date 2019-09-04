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
struct balloon_dev_info {int dummy; } ;
struct virtio_balloon {size_t num_pfns; int /*<<< orphan*/  balloon_lock; int /*<<< orphan*/  deflate_vq; scalar_t__ num_pages; scalar_t__ pfns; struct balloon_dev_info vb_dev_info; } ;
struct page {int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ VIRTIO_BALLOON_PAGES_PER_PAGE ; 
 struct page* balloon_page_dequeue (struct balloon_dev_info*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pages ; 
 int /*<<< orphan*/  release_pages_balloon (struct virtio_balloon*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_pfns (struct virtio_balloon*,scalar_t__,struct page*) ; 
 int /*<<< orphan*/  tell_host (struct virtio_balloon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned leak_balloon(struct virtio_balloon *vb, size_t num)
{
	unsigned num_freed_pages;
	struct page *page;
	struct balloon_dev_info *vb_dev_info = &vb->vb_dev_info;
	LIST_HEAD(pages);

	/* We can only do one array worth at a time. */
	num = min(num, ARRAY_SIZE(vb->pfns));

	mutex_lock(&vb->balloon_lock);
	/* We can't release more pages than taken */
	num = min(num, (size_t)vb->num_pages);
	for (vb->num_pfns = 0; vb->num_pfns < num;
	     vb->num_pfns += VIRTIO_BALLOON_PAGES_PER_PAGE) {
		page = balloon_page_dequeue(vb_dev_info);
		if (!page)
			break;
		set_page_pfns(vb, vb->pfns + vb->num_pfns, page);
		list_add(&page->lru, &pages);
		vb->num_pages -= VIRTIO_BALLOON_PAGES_PER_PAGE;
	}

	num_freed_pages = vb->num_pfns;
	/*
	 * Note that if
	 * virtio_has_feature(vdev, VIRTIO_BALLOON_F_MUST_TELL_HOST);
	 * is true, we *have* to do it in this order
	 */
	if (vb->num_pfns != 0)
		tell_host(vb, vb->deflate_vq);
	release_pages_balloon(vb, &pages);
	mutex_unlock(&vb->balloon_lock);
	return num_freed_pages;
}