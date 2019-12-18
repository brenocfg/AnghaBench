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
struct TYPE_3__ {int spoctl; int i2soctl; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct daio_mgr_ctrl_blk {TYPE_2__ dirty; int /*<<< orphan*/  i2sctl; int /*<<< orphan*/  spoctl; } ;

/* Variables and functions */
 unsigned int I2SCTL_EA ; 
 unsigned int SPOCTL_OE ; 
 int /*<<< orphan*/  set_field (int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static int daio_mgr_enb_dao(void *blk, unsigned int idx)
{
	struct daio_mgr_ctrl_blk *ctl = blk;

	if (idx < 4) {
		/* S/PDIF output */
		set_field(&ctl->spoctl, SPOCTL_OE << (idx*8), 1);
		ctl->dirty.bf.spoctl |= (0x1 << idx);
	} else {
		/* I2S output */
		idx %= 4;
		set_field(&ctl->i2sctl, I2SCTL_EA << (idx*8), 1);
		ctl->dirty.bf.i2soctl |= (0x1 << idx);
	}
	return 0;
}