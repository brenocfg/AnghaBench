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
struct lx6464es {scalar_t__ playback_mute; scalar_t__* mac_address; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MICROBLAZE_IBL_DEFAULT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int lx_dsp_get_mac (struct lx6464es*) ; 
 int lx_init_ethersound_config (struct lx6464es*) ; 
 int lx_init_get_version_features (struct lx6464es*) ; 
 int lx_init_xilinx_reset (struct lx6464es*) ; 
 int lx_init_xilinx_test (struct lx6464es*) ; 
 int /*<<< orphan*/  lx_irq_enable (struct lx6464es*) ; 
 int /*<<< orphan*/  lx_set_granularity (struct lx6464es*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int lx_init_dsp(struct lx6464es *chip)
{
	int err;
	int i;

	dev_dbg(chip->card->dev, "->lx_init_dsp\n");

	dev_dbg(chip->card->dev, "initialize board\n");
	err = lx_init_xilinx_reset(chip);
	if (err)
		return err;

	dev_dbg(chip->card->dev, "testing board\n");
	err = lx_init_xilinx_test(chip);
	if (err)
		return err;

	dev_dbg(chip->card->dev, "initialize ethersound configuration\n");
	err = lx_init_ethersound_config(chip);
	if (err)
		return err;

	lx_irq_enable(chip);

	/** \todo the mac address should be ready by not, but it isn't,
	 *  so we wait for it */
	for (i = 0; i != 1000; ++i) {
		err = lx_dsp_get_mac(chip);
		if (err)
			return err;
		if (chip->mac_address[0] || chip->mac_address[1] || chip->mac_address[2] ||
		    chip->mac_address[3] || chip->mac_address[4] || chip->mac_address[5])
			goto mac_ready;
		msleep(1);
	}
	return -ETIMEDOUT;

mac_ready:
	dev_dbg(chip->card->dev, "mac address ready read after: %dms\n", i);
	dev_info(chip->card->dev,
		 "mac address: %02X.%02X.%02X.%02X.%02X.%02X\n",
		   chip->mac_address[0], chip->mac_address[1], chip->mac_address[2],
		   chip->mac_address[3], chip->mac_address[4], chip->mac_address[5]);

	err = lx_init_get_version_features(chip);
	if (err)
		return err;

	lx_set_granularity(chip, MICROBLAZE_IBL_DEFAULT);

	chip->playback_mute = 0;

	return err;
}