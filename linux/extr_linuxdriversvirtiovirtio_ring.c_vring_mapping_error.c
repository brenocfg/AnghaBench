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
struct TYPE_2__ {int /*<<< orphan*/  vdev; } ;
struct vring_virtqueue {TYPE_1__ vq; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_dma_dev (struct vring_virtqueue const*) ; 
 int /*<<< orphan*/  vring_use_dma_api (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vring_mapping_error(const struct vring_virtqueue *vq,
			       dma_addr_t addr)
{
	if (!vring_use_dma_api(vq->vq.vdev))
		return 0;

	return dma_mapping_error(vring_dma_dev(vq), addr);
}