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
struct vnic_cq {int /*<<< orphan*/ * ctrl; int /*<<< orphan*/  ring; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  svnic_dev_free_desc_ring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void svnic_cq_free(struct vnic_cq *cq)
{
	svnic_dev_free_desc_ring(cq->vdev, &cq->ring);

	cq->ctrl = NULL;
}