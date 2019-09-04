#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtio_balloon {TYPE_2__* vdev; scalar_t__ num_pages; } ;
struct TYPE_5__ {TYPE_1__* config; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* del_vqs ) (TYPE_2__*) ;int /*<<< orphan*/  (* reset ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  leak_balloon (struct virtio_balloon*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  update_balloon_size (struct virtio_balloon*) ; 

__attribute__((used)) static void remove_common(struct virtio_balloon *vb)
{
	/* There might be pages left in the balloon: free them. */
	while (vb->num_pages)
		leak_balloon(vb, vb->num_pages);
	update_balloon_size(vb);

	/* Now we reset the device so we can clean up the queues. */
	vb->vdev->config->reset(vb->vdev);

	vb->vdev->config->del_vqs(vb->vdev);
}