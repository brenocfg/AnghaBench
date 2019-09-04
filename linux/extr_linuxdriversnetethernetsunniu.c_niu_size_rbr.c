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
typedef  int u16 ;
struct rx_ring_info {int rbr_block_size; int rbr_blocks_per_page; int* rbr_sizes; } ;
struct niu {TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ ETH_DATA_LEN ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int min (int,int) ; 

__attribute__((used)) static void niu_size_rbr(struct niu *np, struct rx_ring_info *rp)
{
	u16 bss;

	bss = min(PAGE_SHIFT, 15);

	rp->rbr_block_size = 1 << bss;
	rp->rbr_blocks_per_page = 1 << (PAGE_SHIFT-bss);

	rp->rbr_sizes[0] = 256;
	rp->rbr_sizes[1] = 1024;
	if (np->dev->mtu > ETH_DATA_LEN) {
		switch (PAGE_SIZE) {
		case 4 * 1024:
			rp->rbr_sizes[2] = 4096;
			break;

		default:
			rp->rbr_sizes[2] = 8192;
			break;
		}
	} else {
		rp->rbr_sizes[2] = 2048;
	}
	rp->rbr_sizes[3] = rp->rbr_block_size;
}