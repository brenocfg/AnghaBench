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
struct velocity_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  velocity_free_dma_rings (struct velocity_info*) ; 
 int /*<<< orphan*/  velocity_free_rd_ring (struct velocity_info*) ; 
 int velocity_init_dma_rings (struct velocity_info*) ; 
 int velocity_init_rd_ring (struct velocity_info*) ; 
 int velocity_init_td_ring (struct velocity_info*) ; 
 int /*<<< orphan*/  velocity_set_rxbufsize (struct velocity_info*,int) ; 

__attribute__((used)) static int velocity_init_rings(struct velocity_info *vptr, int mtu)
{
	int ret;

	velocity_set_rxbufsize(vptr, mtu);

	ret = velocity_init_dma_rings(vptr);
	if (ret < 0)
		goto out;

	ret = velocity_init_rd_ring(vptr);
	if (ret < 0)
		goto err_free_dma_rings_0;

	ret = velocity_init_td_ring(vptr);
	if (ret < 0)
		goto err_free_rd_ring_1;
out:
	return ret;

err_free_rd_ring_1:
	velocity_free_rd_ring(vptr);
err_free_dma_rings_0:
	velocity_free_dma_rings(vptr);
	goto out;
}