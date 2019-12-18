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
struct TYPE_2__ {unsigned int (* get_data ) (struct snd_ice1712*) ;int /*<<< orphan*/  (* set_data ) (struct snd_ice1712*,unsigned int) ;} ;
struct snd_ice1712 {TYPE_1__ gpio; struct juli_spec* spec; } ;
struct snd_akm4xxx {struct snd_ice1712** private_data; } ;
struct juli_spec {int /*<<< orphan*/  ak4114; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CMD ; 
 unsigned int GPIO_AK5385A_CKS0 ; 
 unsigned int GPIO_AK5385A_DFS0 ; 
 unsigned int GPIO_AK5385A_DFS1 ; 
 unsigned int GPIO_AK5385A_MASK ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 unsigned char VT1724_AC97_COLD ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ak4114_reinit (int /*<<< orphan*/ ) ; 
 unsigned char snd_akm4xxx_get (struct snd_akm4xxx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_akm4xxx_reset (struct snd_akm4xxx*,int) ; 
 int /*<<< orphan*/  snd_akm4xxx_set (struct snd_akm4xxx*,int /*<<< orphan*/ ,int,unsigned char) ; 
 unsigned int stub1 (struct snd_ice1712*) ; 
 int /*<<< orphan*/  stub2 (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void juli_akm_set_rate_val(struct snd_akm4xxx *ak, unsigned int rate)
{
	unsigned char old, tmp, ak4358_dfs;
	unsigned int ak5385_pins, old_gpio, new_gpio;
	struct snd_ice1712 *ice = ak->private_data[0];
	struct juli_spec *spec = ice->spec;

	if (rate == 0)  /* no hint - S/PDIF input is master or the new spdif
			   input rate undetected, simply return */
		return;

	/* adjust DFS on codecs */
	if (rate > 96000)  {
		ak4358_dfs = 2;
		ak5385_pins = GPIO_AK5385A_DFS1 | GPIO_AK5385A_CKS0;
	} else if (rate > 48000) {
		ak4358_dfs = 1;
		ak5385_pins = GPIO_AK5385A_DFS0;
	} else {
		ak4358_dfs = 0;
		ak5385_pins = 0;
	}
	/* AK5385 first, since it requires cold reset affecting both codecs */
	old_gpio = ice->gpio.get_data(ice);
	new_gpio =  (old_gpio & ~GPIO_AK5385A_MASK) | ak5385_pins;
	/* dev_dbg(ice->card->dev, "JULI - ak5385 set_rate_val: new gpio 0x%x\n",
		new_gpio); */
	ice->gpio.set_data(ice, new_gpio);

	/* cold reset */
	old = inb(ICEMT1724(ice, AC97_CMD));
	outb(old | VT1724_AC97_COLD, ICEMT1724(ice, AC97_CMD));
	udelay(1);
	outb(old & ~VT1724_AC97_COLD, ICEMT1724(ice, AC97_CMD));

	/* AK4358 */
	/* set new value, reset DFS */
	tmp = snd_akm4xxx_get(ak, 0, 2);
	snd_akm4xxx_reset(ak, 1);
	tmp = snd_akm4xxx_get(ak, 0, 2);
	tmp &= ~(0x03 << 4);
	tmp |= ak4358_dfs << 4;
	snd_akm4xxx_set(ak, 0, 2, tmp);
	snd_akm4xxx_reset(ak, 0);

	/* reinit ak4114 */
	snd_ak4114_reinit(spec->ak4114);
}