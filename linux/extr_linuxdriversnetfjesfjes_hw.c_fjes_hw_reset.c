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
struct TYPE_2__ {int reset; } ;
union REG_DCTL {void* reg; TYPE_1__ bits; } ;
struct fjes_hw {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int FJES_DEVICE_RESET_TIMEOUT ; 
 int /*<<< orphan*/  XSCT_DCTL ; 
 int /*<<< orphan*/  msleep (int) ; 
 void* rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,void*) ; 

int fjes_hw_reset(struct fjes_hw *hw)
{
	union REG_DCTL dctl;
	int timeout;

	dctl.reg = 0;
	dctl.bits.reset = 1;
	wr32(XSCT_DCTL, dctl.reg);

	timeout = FJES_DEVICE_RESET_TIMEOUT * 1000;
	dctl.reg = rd32(XSCT_DCTL);
	while ((dctl.bits.reset == 1) && (timeout > 0)) {
		msleep(1000);
		dctl.reg = rd32(XSCT_DCTL);
		timeout -= 1000;
	}

	return timeout > 0 ? 0 : -EIO;
}