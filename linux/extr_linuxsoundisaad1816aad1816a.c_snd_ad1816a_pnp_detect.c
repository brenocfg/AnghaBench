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
struct pnp_card_link {int dummy; } ;
struct pnp_card_device_id {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int SNDRV_CARDS ; 
 int /*<<< orphan*/  ad1816a_devices ; 
 int /*<<< orphan*/ * enable ; 
 int snd_card_ad1816a_probe (int,struct pnp_card_link*,struct pnp_card_device_id const*) ; 

__attribute__((used)) static int snd_ad1816a_pnp_detect(struct pnp_card_link *card,
				  const struct pnp_card_device_id *id)
{
	static int dev;
	int res;

	for ( ; dev < SNDRV_CARDS; dev++) {
		if (!enable[dev])
			continue;
		res = snd_card_ad1816a_probe(dev, card, id);
		if (res < 0)
			return res;
		dev++;
		ad1816a_devices++;
		return 0;
	}
        return -ENODEV;
}