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
struct hw {int dummy; } ;
struct daio_conf {int msr; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2SCTL ; 
 int /*<<< orphan*/  SPICTL ; 
 int /*<<< orphan*/  SPOCTL ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int hw_daio_init(struct hw *hw, const struct daio_conf *info)
{
	u32 i2sorg;
	u32 spdorg;

	/* Read I2S CTL.  Keep original value. */
	/*i2sorg = hw_read_20kx(hw, I2SCTL);*/
	i2sorg = 0x94040404; /* enable all audio out and I2S-D input */
	/* Program I2S with proper master sample rate and enable
	 * the correct I2S channel. */
	i2sorg &= 0xfffffffc;

	/* Enable S/PDIF-out-A in fixed 24-bit data
	 * format and default to 48kHz. */
	/* Disable all before doing any changes. */
	hw_write_20kx(hw, SPOCTL, 0x0);
	spdorg = 0x05;

	switch (info->msr) {
	case 1:
		i2sorg |= 1;
		spdorg |= (0x0 << 6);
		break;
	case 2:
		i2sorg |= 2;
		spdorg |= (0x1 << 6);
		break;
	case 4:
		i2sorg |= 3;
		spdorg |= (0x2 << 6);
		break;
	default:
		i2sorg |= 1;
		break;
	}

	hw_write_20kx(hw, I2SCTL, i2sorg);
	hw_write_20kx(hw, SPOCTL, spdorg);

	/* Enable S/PDIF-in-A in fixed 24-bit data format. */
	/* Disable all before doing any changes. */
	hw_write_20kx(hw, SPICTL, 0x0);
	mdelay(1);
	spdorg = 0x0a0a0a0a;
	hw_write_20kx(hw, SPICTL, spdorg);
	mdelay(1);

	return 0;
}