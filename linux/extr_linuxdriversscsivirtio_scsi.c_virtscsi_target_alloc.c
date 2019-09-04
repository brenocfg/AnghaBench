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
struct virtio_scsi_target_state {int /*<<< orphan*/ * req_vq; int /*<<< orphan*/  tgt_seq; } ;
struct virtio_scsi {int /*<<< orphan*/ * req_vqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {struct virtio_scsi_target_state* hostdata; TYPE_1__ dev; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 struct virtio_scsi_target_state* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seqcount_init (int /*<<< orphan*/ *) ; 
 struct virtio_scsi* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int virtscsi_target_alloc(struct scsi_target *starget)
{
	struct Scsi_Host *sh = dev_to_shost(starget->dev.parent);
	struct virtio_scsi *vscsi = shost_priv(sh);

	struct virtio_scsi_target_state *tgt =
				kmalloc(sizeof(*tgt), GFP_KERNEL);
	if (!tgt)
		return -ENOMEM;

	seqcount_init(&tgt->tgt_seq);
	tgt->req_vq = &vscsi->req_vqs[0];

	starget->hostdata = tgt;
	return 0;
}