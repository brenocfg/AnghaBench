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
typedef  int /*<<< orphan*/  u32 ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 unsigned int S626_I2C_BUSY ; 
 unsigned int S626_I2C_ERR ; 
 int /*<<< orphan*/  S626_MC2_UPLD_IIC ; 
 scalar_t__ S626_P_I2CCTRL ; 
 int /*<<< orphan*/  S626_P_MC2 ; 
 int comedi_timeout (struct comedi_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  s626_i2c_handshake_eoc ; 
 int /*<<< orphan*/  s626_mc_enable (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s626_i2c_handshake(struct comedi_device *dev, u32 val)
{
	unsigned int ctrl;
	int ret;

	/* Write I2C command to I2C Transfer Control shadow register */
	writel(val, dev->mmio + S626_P_I2CCTRL);

	/*
	 * Upload I2C shadow registers into working registers and
	 * wait for upload confirmation.
	 */
	s626_mc_enable(dev, S626_MC2_UPLD_IIC, S626_P_MC2);
	ret = comedi_timeout(dev, NULL, NULL, s626_i2c_handshake_eoc, 0);
	if (ret)
		return ret;

	/* Wait until I2C bus transfer is finished or an error occurs */
	do {
		ctrl = readl(dev->mmio + S626_P_I2CCTRL);
	} while ((ctrl & (S626_I2C_BUSY | S626_I2C_ERR)) == S626_I2C_BUSY);

	/* Return non-zero if I2C error occurred */
	return ctrl & S626_I2C_ERR;
}