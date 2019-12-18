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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_AD_SERIAL_CFG ; 
 int /*<<< orphan*/  AD1980_VENDOR_ID ; 
 int /*<<< orphan*/  AD1980_VENDOR_MASK ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_ac97_reset (struct snd_ac97*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_ac97* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad1980_reset(struct snd_soc_component *component, int try_warm)
{
	struct snd_ac97 *ac97 = snd_soc_component_get_drvdata(component);
	unsigned int retry_cnt = 0;
	int ret;

	do {
		ret = snd_ac97_reset(ac97, true, AD1980_VENDOR_ID,
			AD1980_VENDOR_MASK);
		if (ret >= 0)
			return 0;

		/*
		 * Set bit 16slot in register 74h, then every slot will has only
		 * 16 bits. This command is sent out in 20bit mode, in which
		 * case the first nibble of data is eaten by the addr. (Tag is
		 * always 16 bit)
		 */
		snd_soc_component_write(component, AC97_AD_SERIAL_CFG, 0x9900);

	} while (retry_cnt++ < 10);

	dev_err(component->dev, "Failed to reset: AC97 link error\n");

	return -EIO;
}