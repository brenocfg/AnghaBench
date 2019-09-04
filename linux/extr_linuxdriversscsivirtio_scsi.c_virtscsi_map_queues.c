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
struct virtio_scsi {int /*<<< orphan*/  vdev; } ;
struct Scsi_Host {int /*<<< orphan*/  tag_set; } ;

/* Variables and functions */
 int blk_mq_virtio_map_queues (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct virtio_scsi* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int virtscsi_map_queues(struct Scsi_Host *shost)
{
	struct virtio_scsi *vscsi = shost_priv(shost);

	return blk_mq_virtio_map_queues(&shost->tag_set, vscsi->vdev, 2);
}