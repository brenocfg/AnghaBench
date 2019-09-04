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
struct snd_ice1712 {int /*<<< orphan*/  gpio_mutex; struct hoontech_spec* spec; } ;
struct hoontech_spec {int /*<<< orphan*/ * boxbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE1712_STDSP24_0_BOX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ICE1712_STDSP24_1_CHN1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ICE1712_STDSP24_1_CHN2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ICE1712_STDSP24_1_CHN3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ICE1712_STDSP24_2_CHN4 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ICE1712_STDSP24_2_MIDI1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ice1712_stdsp24_gpio_write (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_ice1712_stdsp24_box_channel(struct snd_ice1712 *ice, int box, int chn, int activate)
{
	struct hoontech_spec *spec = ice->spec;

	mutex_lock(&ice->gpio_mutex);

	/* select box */
	ICE1712_STDSP24_0_BOX(spec->boxbits, box);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[0]);

	/* prepare for write */
	if (chn == 3)
		ICE1712_STDSP24_2_CHN4(spec->boxbits, 0);
	ICE1712_STDSP24_2_MIDI1(spec->boxbits, activate);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[2]);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[3]);

	ICE1712_STDSP24_1_CHN1(spec->boxbits, 1);
	ICE1712_STDSP24_1_CHN2(spec->boxbits, 1);
	ICE1712_STDSP24_1_CHN3(spec->boxbits, 1);
	ICE1712_STDSP24_2_CHN4(spec->boxbits, 1);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[1]);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[2]);
	udelay(100);
	if (chn == 3) {
		ICE1712_STDSP24_2_CHN4(spec->boxbits, 0);
		snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[2]);
	} else {
		switch (chn) {
		case 0:	ICE1712_STDSP24_1_CHN1(spec->boxbits, 0); break;
		case 1:	ICE1712_STDSP24_1_CHN2(spec->boxbits, 0); break;
		case 2:	ICE1712_STDSP24_1_CHN3(spec->boxbits, 0); break;
		}
		snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[1]);
	}
	udelay(100);
	ICE1712_STDSP24_1_CHN1(spec->boxbits, 1);
	ICE1712_STDSP24_1_CHN2(spec->boxbits, 1);
	ICE1712_STDSP24_1_CHN3(spec->boxbits, 1);
	ICE1712_STDSP24_2_CHN4(spec->boxbits, 1);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[1]);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[2]);
	udelay(100);

	ICE1712_STDSP24_2_MIDI1(spec->boxbits, 0);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[2]);

	mutex_unlock(&ice->gpio_mutex);
}