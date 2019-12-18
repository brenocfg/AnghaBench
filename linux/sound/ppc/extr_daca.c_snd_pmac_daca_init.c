#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pmac {int /*<<< orphan*/  resume; TYPE_2__* card; int /*<<< orphan*/  mixer_free; struct pmac_daca* mixer_data; } ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  init_client; int /*<<< orphan*/  addr; } ;
struct pmac_daca {int amp_on; TYPE_1__ i2c; } ;
struct TYPE_4__ {int /*<<< orphan*/  mixername; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DACA_I2C_ADDR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  daca_cleanup ; 
 int /*<<< orphan*/  daca_init_client ; 
 int /*<<< orphan*/ * daca_mixers ; 
 int /*<<< orphan*/  daca_resume ; 
 struct pmac_daca* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*) ; 
 int snd_ctl_add (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_pmac*) ; 
 int snd_pmac_keywest_init (TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int snd_pmac_daca_init(struct snd_pmac *chip)
{
	int i, err;
	struct pmac_daca *mix;

	request_module("i2c-powermac");

	mix = kzalloc(sizeof(*mix), GFP_KERNEL);
	if (! mix)
		return -ENOMEM;
	chip->mixer_data = mix;
	chip->mixer_free = daca_cleanup;
	mix->amp_on = 1; /* default on */

	mix->i2c.addr = DACA_I2C_ADDR;
	mix->i2c.init_client = daca_init_client;
	mix->i2c.name = "DACA";
	if ((err = snd_pmac_keywest_init(&mix->i2c)) < 0)
		return err;

	/*
	 * build mixers
	 */
	strcpy(chip->card->mixername, "PowerMac DACA");

	for (i = 0; i < ARRAY_SIZE(daca_mixers); i++) {
		if ((err = snd_ctl_add(chip->card, snd_ctl_new1(&daca_mixers[i], chip))) < 0)
			return err;
	}

#ifdef CONFIG_PM
	chip->resume = daca_resume;
#endif

	return 0;
}