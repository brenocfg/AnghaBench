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
struct snd_ice1712 {int dummy; } ;
struct snd_akm4xxx {struct snd_ice1712** private_data; scalar_t__* private_value; } ;
struct snd_ak4xxx_private {int /*<<< orphan*/  cs_addr; int /*<<< orphan*/  cs_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE1712_DELTA_CODEC_CHIP_A ; 
 int /*<<< orphan*/  ICE1712_DELTA_CODEC_CHIP_B ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 

__attribute__((used)) static void delta_ak4524_lock(struct snd_akm4xxx *ak, int chip)
{
        struct snd_ak4xxx_private *priv = (void *)ak->private_value[0];
        struct snd_ice1712 *ice = ak->private_data[0];

	snd_ice1712_save_gpio_status(ice);
	priv->cs_mask =
	priv->cs_addr = chip == 0 ? ICE1712_DELTA_CODEC_CHIP_A :
				    ICE1712_DELTA_CODEC_CHIP_B;
}