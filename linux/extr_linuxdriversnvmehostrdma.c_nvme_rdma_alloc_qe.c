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
struct nvme_rdma_qe {int /*<<< orphan*/ * data; int /*<<< orphan*/  dma; } ;
struct ib_device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ib_dma_map_single (struct ib_device*,int /*<<< orphan*/ *,size_t,int) ; 
 scalar_t__ ib_dma_mapping_error (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_rdma_alloc_qe(struct ib_device *ibdev, struct nvme_rdma_qe *qe,
		size_t capsule_size, enum dma_data_direction dir)
{
	qe->data = kzalloc(capsule_size, GFP_KERNEL);
	if (!qe->data)
		return -ENOMEM;

	qe->dma = ib_dma_map_single(ibdev, qe->data, capsule_size, dir);
	if (ib_dma_mapping_error(ibdev, qe->dma)) {
		kfree(qe->data);
		qe->data = NULL;
		return -ENOMEM;
	}

	return 0;
}