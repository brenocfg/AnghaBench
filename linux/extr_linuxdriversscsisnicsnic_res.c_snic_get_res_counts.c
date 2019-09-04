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
struct snic {scalar_t__ wq_count; scalar_t__ cq_count; scalar_t__ intr_count; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_CQ ; 
 int /*<<< orphan*/  RES_TYPE_INTR_CTRL ; 
 int /*<<< orphan*/  RES_TYPE_WQ ; 
 int /*<<< orphan*/  SNIC_BUG_ON (int) ; 
 void* svnic_dev_get_res_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
snic_get_res_counts(struct snic *snic)
{
	snic->wq_count = svnic_dev_get_res_count(snic->vdev, RES_TYPE_WQ);
	SNIC_BUG_ON(snic->wq_count == 0);
	snic->cq_count = svnic_dev_get_res_count(snic->vdev, RES_TYPE_CQ);
	SNIC_BUG_ON(snic->cq_count == 0);
	snic->intr_count = svnic_dev_get_res_count(snic->vdev,
						  RES_TYPE_INTR_CTRL);
	SNIC_BUG_ON(snic->intr_count == 0);
}