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
struct virtio_scsi_target_state {int dummy; } ;
struct scsi_target {struct virtio_scsi_target_state* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct virtio_scsi_target_state*) ; 

__attribute__((used)) static void virtscsi_target_destroy(struct scsi_target *starget)
{
	struct virtio_scsi_target_state *tgt = starget->hostdata;
	kfree(tgt);
}