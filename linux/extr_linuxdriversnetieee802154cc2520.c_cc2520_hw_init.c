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
typedef  scalar_t__ u8 ;
struct cc2520_private {scalar_t__ amplified; TYPE_1__* spi; } ;
struct cc2520_platform_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC2520_ADCTEST0 ; 
 int /*<<< orphan*/  CC2520_ADCTEST1 ; 
 int /*<<< orphan*/  CC2520_ADCTEST2 ; 
 int /*<<< orphan*/  CC2520_AGCCTRL1 ; 
 int /*<<< orphan*/  CC2520_CCACTRL0 ; 
 int /*<<< orphan*/  CC2520_FIFOPCTRL ; 
 int /*<<< orphan*/  CC2520_FRMCTRL1 ; 
 int /*<<< orphan*/  CC2520_FSCAL1 ; 
 int /*<<< orphan*/  CC2520_FSCTRL ; 
 int /*<<< orphan*/  CC2520_FSMSTAT1 ; 
 int /*<<< orphan*/  CC2520_GPIOCTRL0 ; 
 int /*<<< orphan*/  CC2520_GPIOCTRL5 ; 
 int /*<<< orphan*/  CC2520_GPIOPOLARITY ; 
 int /*<<< orphan*/  CC2520_MDMCTRL0 ; 
 int /*<<< orphan*/  CC2520_MDMCTRL1 ; 
 int /*<<< orphan*/  CC2520_RXCTRL ; 
 scalar_t__ CC2520_STATUS_XOSC32M_STABLE ; 
 int /*<<< orphan*/  CC2520_TXCTRL ; 
 int EINVAL ; 
 int FRMCTRL1_IGNORE_TX_UNDERF ; 
 int FRMCTRL1_SET_RXENMASK_ON_TX ; 
 scalar_t__ STATE_IDLE ; 
 int cc2520_get_platform_data (TYPE_1__*,struct cc2520_platform_data*) ; 
 int cc2520_get_status (struct cc2520_private*,scalar_t__*) ; 
 int cc2520_read_register (struct cc2520_private*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int cc2520_write_register (struct cc2520_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cc2520_hw_init(struct cc2520_private *priv)
{
	u8 status = 0, state = 0xff;
	int ret;
	int timeout = 100;
	struct cc2520_platform_data pdata;

	ret = cc2520_get_platform_data(priv->spi, &pdata);
	if (ret)
		goto err_ret;

	ret = cc2520_read_register(priv, CC2520_FSMSTAT1, &state);
	if (ret)
		goto err_ret;

	if (state != STATE_IDLE)
		return -EINVAL;

	do {
		ret = cc2520_get_status(priv, &status);
		if (ret)
			goto err_ret;

		if (timeout-- <= 0) {
			dev_err(&priv->spi->dev, "oscillator start failed!\n");
			return ret;
		}
		udelay(1);
	} while (!(status & CC2520_STATUS_XOSC32M_STABLE));

	dev_vdbg(&priv->spi->dev, "oscillator brought up\n");

	/* If the CC2520 is connected to a CC2591 amplifier, we must both
	 * configure GPIOs on the CC2520 to correctly configure the CC2591
	 * and change a couple settings of the CC2520 to work with the
	 * amplifier. See section 8 page 17 of TI application note AN065.
	 * http://www.ti.com/lit/an/swra229a/swra229a.pdf
	 */
	if (priv->amplified) {
		ret = cc2520_write_register(priv, CC2520_AGCCTRL1, 0x16);
		if (ret)
			goto err_ret;

		ret = cc2520_write_register(priv, CC2520_GPIOCTRL0, 0x46);
		if (ret)
			goto err_ret;

		ret = cc2520_write_register(priv, CC2520_GPIOCTRL5, 0x47);
		if (ret)
			goto err_ret;

		ret = cc2520_write_register(priv, CC2520_GPIOPOLARITY, 0x1e);
		if (ret)
			goto err_ret;

		ret = cc2520_write_register(priv, CC2520_TXCTRL, 0xc1);
		if (ret)
			goto err_ret;
	} else {
		ret = cc2520_write_register(priv, CC2520_AGCCTRL1, 0x11);
		if (ret)
			goto err_ret;
	}

	/* Registers default value: section 28.1 in Datasheet */

	/* Set the CCA threshold to -50 dBm. This seems to have been copied
	 * from the TinyOS CC2520 driver and is much higher than the -84 dBm
	 * threshold suggested in the datasheet.
	 */
	ret = cc2520_write_register(priv, CC2520_CCACTRL0, 0x1A);
	if (ret)
		goto err_ret;

	ret = cc2520_write_register(priv, CC2520_MDMCTRL0, 0x85);
	if (ret)
		goto err_ret;

	ret = cc2520_write_register(priv, CC2520_MDMCTRL1, 0x14);
	if (ret)
		goto err_ret;

	ret = cc2520_write_register(priv, CC2520_RXCTRL, 0x3f);
	if (ret)
		goto err_ret;

	ret = cc2520_write_register(priv, CC2520_FSCTRL, 0x5a);
	if (ret)
		goto err_ret;

	ret = cc2520_write_register(priv, CC2520_FSCAL1, 0x2b);
	if (ret)
		goto err_ret;

	ret = cc2520_write_register(priv, CC2520_ADCTEST0, 0x10);
	if (ret)
		goto err_ret;

	ret = cc2520_write_register(priv, CC2520_ADCTEST1, 0x0e);
	if (ret)
		goto err_ret;

	ret = cc2520_write_register(priv, CC2520_ADCTEST2, 0x03);
	if (ret)
		goto err_ret;

	/* Configure registers correctly for this driver. */
	ret = cc2520_write_register(priv, CC2520_FRMCTRL1,
				    FRMCTRL1_SET_RXENMASK_ON_TX |
				    FRMCTRL1_IGNORE_TX_UNDERF);
	if (ret)
		goto err_ret;

	ret = cc2520_write_register(priv, CC2520_FIFOPCTRL, 127);
	if (ret)
		goto err_ret;

	return 0;

err_ret:
	return ret;
}