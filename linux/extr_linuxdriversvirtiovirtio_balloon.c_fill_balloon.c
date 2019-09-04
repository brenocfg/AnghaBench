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
struct virtio_balloon {unsigned int num_pfns; int /*<<< orphan*/  balloon_lock; int /*<<< orphan*/  inflate_vq; TYPE_1__* vdev; int /*<<< orphan*/  num_pages; scalar_t__ pfns; int /*<<< orphan*/  vb_dev_info; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_F_DEFLATE_ON_OOM ; 
 scalar_t__ VIRTIO_BALLOON_PAGES_PER_PAGE ; 
 int /*<<< orphan*/  adjust_managed_page_count (struct page*,int) ; 
 struct page* balloon_page_alloc () ; 
 int /*<<< orphan*/  balloon_page_enqueue (int /*<<< orphan*/ *,struct page*) ; 
 struct page* balloon_page_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  balloon_page_push (int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  dev_info_ratelimited (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pages ; 
 int /*<<< orphan*/  set_page_pfns (struct virtio_balloon*,scalar_t__,struct page*) ; 
 int /*<<< orphan*/  tell_host (struct virtio_balloon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_has_feature (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned fill_balloon(struct virtio_balloon *vb, size_t num)
{
	unsigned num_allocated_pages;
	unsigned num_pfns;
	struct page *page;
	LIST_HEAD(pages);

	/* We can only do one array worth at a time. */
	num = min(num, ARRAY_SIZE(vb->pfns));

	for (num_pfns = 0; num_pfns < num;
	     num_pfns += VIRTIO_BALLOON_PAGES_PER_PAGE) {
		struct page *page = balloon_page_alloc();

		if (!page) {
			dev_info_ratelimited(&vb->vdev->dev,
					     "Out of puff! Can't get %u pages\n",
					     VIRTIO_BALLOON_PAGES_PER_PAGE);
			/* Sleep for at least 1/5 of a second before retry. */
			msleep(200);
			break;
		}

		balloon_page_push(&pages, page);
	}

	mutex_lock(&vb->balloon_lock);

	vb->num_pfns = 0;

	while ((page = balloon_page_pop(&pages))) {
		balloon_page_enqueue(&vb->vb_dev_info, page);

		set_page_pfns(vb, vb->pfns + vb->num_pfns, page);
		vb->num_pages += VIRTIO_BALLOON_PAGES_PER_PAGE;
		if (!virtio_has_feature(vb->vdev,
					VIRTIO_BALLOON_F_DEFLATE_ON_OOM))
			adjust_managed_page_count(page, -1);
		vb->num_pfns += VIRTIO_BALLOON_PAGES_PER_PAGE;
	}

	num_allocated_pages = vb->num_pfns;
	/* Did we get any? */
	if (vb->num_pfns != 0)
		tell_host(vb, vb->inflate_vq);
	mutex_unlock(&vb->balloon_lock);

	return num_allocated_pages;
}