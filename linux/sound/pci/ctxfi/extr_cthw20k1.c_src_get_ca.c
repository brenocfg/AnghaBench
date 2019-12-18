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
struct TYPE_3__ {scalar_t__ ca; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct src_rsc_ctrl_blk {int /*<<< orphan*/  ca; TYPE_2__ dirty; } ;
struct hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ SRCCA ; 
 int /*<<< orphan*/  SRCCA_CA ; 
 int get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_read_20kx (struct hw*,scalar_t__) ; 

__attribute__((used)) static int src_get_ca(struct hw *hw, unsigned int idx, void *blk)
{
	struct src_rsc_ctrl_blk *ctl = blk;

	ctl->ca = hw_read_20kx(hw, SRCCA+idx*0x100);
	ctl->dirty.bf.ca = 0;

	return get_field(ctl->ca, SRCCA_CA);
}