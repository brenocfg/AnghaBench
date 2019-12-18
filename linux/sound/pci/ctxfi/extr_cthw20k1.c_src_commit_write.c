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
struct TYPE_3__ {scalar_t__ ctl; scalar_t__ ccr; scalar_t__ ca; scalar_t__ la; scalar_t__ sa; scalar_t__ mpr; scalar_t__ czbfs; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct src_rsc_ctrl_blk {int mpr; int sa; int la; int ca; int ccr; int ctl; TYPE_2__ dirty; } ;
struct hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ PMOPHI ; 
 scalar_t__ PMOPLO ; 
 scalar_t__ PRING_LO_HI ; 
 scalar_t__ SRCCA ; 
 scalar_t__ SRCCCR ; 
 scalar_t__ SRCCF ; 
 scalar_t__ SRCCTL ; 
 scalar_t__ SRCDN0Z ; 
 scalar_t__ SRCDN1Z ; 
 scalar_t__ SRCLA ; 
 scalar_t__ SRCSA ; 
 scalar_t__ SRCUPZ ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,scalar_t__,int) ; 
 unsigned int src_param_pitch_mixer (unsigned int) ; 

__attribute__((used)) static int src_commit_write(struct hw *hw, unsigned int idx, void *blk)
{
	struct src_rsc_ctrl_blk *ctl = blk;
	int i;

	if (ctl->dirty.bf.czbfs) {
		/* Clear Z-Buffer registers */
		for (i = 0; i < 8; i++)
			hw_write_20kx(hw, SRCUPZ+idx*0x100+i*0x4, 0);

		for (i = 0; i < 4; i++)
			hw_write_20kx(hw, SRCDN0Z+idx*0x100+i*0x4, 0);

		for (i = 0; i < 8; i++)
			hw_write_20kx(hw, SRCDN1Z+idx*0x100+i*0x4, 0);

		ctl->dirty.bf.czbfs = 0;
	}
	if (ctl->dirty.bf.mpr) {
		/* Take the parameter mixer resource in the same group as that
		 * the idx src is in for simplicity. Unlike src, all conjugate
		 * parameter mixer resources must be programmed for
		 * corresponding conjugate src resources. */
		unsigned int pm_idx = src_param_pitch_mixer(idx);
		hw_write_20kx(hw, PRING_LO_HI+4*pm_idx, ctl->mpr);
		hw_write_20kx(hw, PMOPLO+8*pm_idx, 0x3);
		hw_write_20kx(hw, PMOPHI+8*pm_idx, 0x0);
		ctl->dirty.bf.mpr = 0;
	}
	if (ctl->dirty.bf.sa) {
		hw_write_20kx(hw, SRCSA+idx*0x100, ctl->sa);
		ctl->dirty.bf.sa = 0;
	}
	if (ctl->dirty.bf.la) {
		hw_write_20kx(hw, SRCLA+idx*0x100, ctl->la);
		ctl->dirty.bf.la = 0;
	}
	if (ctl->dirty.bf.ca) {
		hw_write_20kx(hw, SRCCA+idx*0x100, ctl->ca);
		ctl->dirty.bf.ca = 0;
	}

	/* Write srccf register */
	hw_write_20kx(hw, SRCCF+idx*0x100, 0x0);

	if (ctl->dirty.bf.ccr) {
		hw_write_20kx(hw, SRCCCR+idx*0x100, ctl->ccr);
		ctl->dirty.bf.ccr = 0;
	}
	if (ctl->dirty.bf.ctl) {
		hw_write_20kx(hw, SRCCTL+idx*0x100, ctl->ctl);
		ctl->dirty.bf.ctl = 0;
	}

	return 0;
}