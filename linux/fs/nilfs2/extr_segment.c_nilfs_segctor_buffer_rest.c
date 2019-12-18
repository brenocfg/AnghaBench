#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nilfs_sc_info {size_t sc_segbuf_nblocks; size_t sc_nblk_this_inc; TYPE_2__* sc_curseg; } ;
struct TYPE_3__ {size_t nblocks; } ;
struct TYPE_4__ {TYPE_1__ sb_sum; } ;

/* Variables and functions */

__attribute__((used)) static size_t nilfs_segctor_buffer_rest(struct nilfs_sc_info *sci)
{
	/* Remaining number of blocks within segment buffer */
	return sci->sc_segbuf_nblocks -
		(sci->sc_nblk_this_inc + sci->sc_curseg->sb_sum.nblocks);
}