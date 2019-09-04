#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtnet_info {TYPE_2__* vdev; } ;
struct TYPE_4__ {TYPE_1__* config; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reset ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free_receive_bufs (struct virtnet_info*) ; 
 int /*<<< orphan*/  free_receive_page_frags (struct virtnet_info*) ; 
 int /*<<< orphan*/  free_unused_bufs (struct virtnet_info*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  virtnet_del_vqs (struct virtnet_info*) ; 

__attribute__((used)) static void remove_vq_common(struct virtnet_info *vi)
{
	vi->vdev->config->reset(vi->vdev);

	/* Free unused buffers in both send and recv, if any. */
	free_unused_bufs(vi);

	free_receive_bufs(vi);

	free_receive_page_frags(vi);

	virtnet_del_vqs(vi);
}