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
struct TYPE_4__ {scalar_t__ enbsa; } ;
struct TYPE_3__ {int data; TYPE_2__ bf; } ;
struct src_mgr_ctrl_blk {TYPE_1__ dirty; int /*<<< orphan*/ * enb; int /*<<< orphan*/  enbsa; } ;
struct hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ SRCENB ; 
 scalar_t__ SRCENBS ; 
 int /*<<< orphan*/  SRCENBSTAT ; 
 unsigned int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int src_mgr_commit_write(struct hw *hw, void *blk)
{
	struct src_mgr_ctrl_blk *ctl = blk;
	int i;
	unsigned int ret;

	if (ctl->dirty.bf.enbsa) {
		do {
			ret = hw_read_20kx(hw, SRCENBSTAT);
		} while (ret & 0x1);
		hw_write_20kx(hw, SRCENBS, ctl->enbsa);
		ctl->dirty.bf.enbsa = 0;
	}
	for (i = 0; i < 8; i++) {
		if ((ctl->dirty.data & (0x1 << i))) {
			hw_write_20kx(hw, SRCENB+(i*0x100), ctl->enb[i]);
			ctl->dirty.data &= ~(0x1 << i);
		}
	}

	return 0;
}