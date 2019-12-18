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
typedef  int u32 ;
typedef  int u16 ;
struct hw {scalar_t__ model; } ;
struct dac_conf {int msr; } ;

/* Variables and functions */
 scalar_t__ CTSB055X ; 
 int /*<<< orphan*/  GPIO ; 
 scalar_t__ hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 unsigned int hw_read_pci (struct hw*,int) ; 
 int /*<<< orphan*/  hw_reset_dac (struct hw*) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw_write_pci (struct hw*,int,int) ; 
 int /*<<< orphan*/  i2c_lock (struct hw*) ; 
 scalar_t__ i2c_unlock (struct hw*) ; 
 int /*<<< orphan*/  i2c_write (struct hw*,int,int,int) ; 

__attribute__((used)) static int hw_dac_init(struct hw *hw, const struct dac_conf *info)
{
	u32 data;
	u16 gpioorg;
	unsigned int ret;

	if (hw->model == CTSB055X) {
		/* SB055x, unmute outputs */
		gpioorg = (u16)hw_read_20kx(hw, GPIO);
		gpioorg &= 0xffbf;	/* set GPIO6 to low */
		gpioorg |= 2;		/* set GPIO1 to high */
		hw_write_20kx(hw, GPIO, gpioorg);
		return 0;
	}

	/* mute outputs */
	gpioorg = (u16)hw_read_20kx(hw, GPIO);
	gpioorg &= 0xffbf;
	hw_write_20kx(hw, GPIO, gpioorg);

	hw_reset_dac(hw);

	if (i2c_unlock(hw))
		return -1;

	hw_write_pci(hw, 0xEC, 0x05);  /* write to i2c status control */
	do {
		ret = hw_read_pci(hw, 0xEC);
	} while (!(ret & 0x800000));

	switch (info->msr) {
	case 1:
		data = 0x24;
		break;
	case 2:
		data = 0x25;
		break;
	case 4:
		data = 0x26;
		break;
	default:
		data = 0x24;
		break;
	}

	i2c_write(hw, 0x00180080, 0x06, data);
	i2c_write(hw, 0x00180080, 0x09, data);
	i2c_write(hw, 0x00180080, 0x0c, data);
	i2c_write(hw, 0x00180080, 0x0f, data);

	i2c_lock(hw);

	/* unmute outputs */
	gpioorg = (u16)hw_read_20kx(hw, GPIO);
	gpioorg = gpioorg | 0x40;
	hw_write_20kx(hw, GPIO, gpioorg);

	return 0;
}