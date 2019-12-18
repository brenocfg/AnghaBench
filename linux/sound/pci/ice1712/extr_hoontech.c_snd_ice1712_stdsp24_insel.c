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
 int /*<<< orphan*/  ICE1712_STDSP24_3_INSEL (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ice1712_stdsp24_gpio_write (struct snd_ice1712*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ice1712_stdsp24_insel(struct snd_ice1712 *ice, int activate)
{
	struct hoontech_spec *spec = ice->spec;
	mutex_lock(&ice->gpio_mutex);
	ICE1712_STDSP24_3_INSEL(spec->boxbits, activate);
	snd_ice1712_stdsp24_gpio_write(ice, spec->boxbits[3]);
	mutex_unlock(&ice->gpio_mutex);
}