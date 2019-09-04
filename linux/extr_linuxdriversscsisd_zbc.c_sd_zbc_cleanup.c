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
struct scsi_disk {TYPE_1__* disk; } ;
struct request_queue {scalar_t__ nr_zones; int /*<<< orphan*/ * seq_zones_wlock; int /*<<< orphan*/ * seq_zones_bitmap; } ;
struct TYPE_2__ {struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sd_zbc_cleanup(struct scsi_disk *sdkp)
{
	struct request_queue *q = sdkp->disk->queue;

	kfree(q->seq_zones_bitmap);
	q->seq_zones_bitmap = NULL;

	kfree(q->seq_zones_wlock);
	q->seq_zones_wlock = NULL;

	q->nr_zones = 0;
}