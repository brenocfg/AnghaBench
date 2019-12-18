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
struct ct_atc {TYPE_1__* card; int /*<<< orphan*/  chip_name; } ;
typedef  enum CTALSADEVS { ____Placeholder_CTALSADEVS } CTALSADEVS ;
struct TYPE_4__ {int (* create ) (struct ct_atc*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  public_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t MIXER ; 
 int NUM_CTALSADEVS ; 
 TYPE_2__* alsa_dev_funcs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct ct_atc*,int,int /*<<< orphan*/ ) ; 

int ct_atc_create_alsa_devs(struct ct_atc *atc)
{
	enum CTALSADEVS i;
	int err;

	alsa_dev_funcs[MIXER].public_name = atc->chip_name;

	for (i = 0; i < NUM_CTALSADEVS; i++) {
		if (!alsa_dev_funcs[i].create)
			continue;

		err = alsa_dev_funcs[i].create(atc, i,
				alsa_dev_funcs[i].public_name);
		if (err) {
			dev_err(atc->card->dev,
				"Creating alsa device %d failed!\n", i);
			return err;
		}
	}

	return 0;
}