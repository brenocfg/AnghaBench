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
struct rx_ring_info {int rbr_blocks_per_page; int rbr_index; int rbr_table_size; } ;
struct niu {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int niu_rbr_add_page (struct niu*,struct rx_ring_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int niu_rbr_fill(struct niu *np, struct rx_ring_info *rp, gfp_t mask)
{
	int blocks_per_page = rp->rbr_blocks_per_page;
	int err, index = rp->rbr_index;

	err = 0;
	while (index < (rp->rbr_table_size - blocks_per_page)) {
		err = niu_rbr_add_page(np, rp, mask, index);
		if (unlikely(err))
			break;

		index += blocks_per_page;
	}

	rp->rbr_index = index;
	return err;
}