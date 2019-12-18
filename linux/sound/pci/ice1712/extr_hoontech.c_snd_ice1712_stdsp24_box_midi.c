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
 int /*<<< orphan*/  ICE1712_STDSP24_2_MIDI1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ICE1712_STDSP24_2_MIDIIN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ice1712_stdsp24_gpio_write (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_ice1712_stdsp24_box_midi(struct snd_ice1712 *ice, int box, int master)
{
	struct hoontech_spec *spec = ice->spec;

	mutex_lock(&ice->gpio_mutex);

	/* select box */
	ICE1712_STDSP24_0_BOX(spec->boxbits, box);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[0]);

	ICE1712_STDSP24_2_MIDIIN(spec->boxbits, 1);
	ICE1712_STDSP24_2_MIDI1(spec->boxbits, master);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[2]);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[3]);

	udelay(100);
	
	ICE1712_STDSP24_2_MIDIIN(spec->boxbits, 0);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[2]);
	
	mdelay(10);
	
	ICE1712_STDSP24_2_MIDIIN(spec->boxbits, 1);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[2]);

	mutex_unlock(&ice->gpio_mutex);
}