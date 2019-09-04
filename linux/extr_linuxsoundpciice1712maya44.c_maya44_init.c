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
struct snd_maya44 {int /*<<< orphan*/ * wm; struct snd_ice1712* ice; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_pro_rate; } ;
struct snd_ice1712 {int num_total_dacs; int num_total_adcs; int force_rdma1; int own_routing; TYPE_1__ gpio; int /*<<< orphan*/ * hw_rates; scalar_t__ akm_codecs; struct snd_maya44* spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAYA_LINE_IN ; 
 int /*<<< orphan*/  dac_rates ; 
 struct snd_maya44* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rate ; 
 int /*<<< orphan*/ * wm8776_addr ; 
 int /*<<< orphan*/  wm8776_init (struct snd_ice1712*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8776_select_input (struct snd_maya44*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int maya44_init(struct snd_ice1712 *ice)
{
	int i;
	struct snd_maya44 *chip;

	chip = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;
	mutex_init(&chip->mutex);
	chip->ice = ice;
	ice->spec = chip;

	/* initialise codecs */
	ice->num_total_dacs = 4;
	ice->num_total_adcs = 4;
	ice->akm_codecs = 0;

	for (i = 0; i < 2; i++) {
		wm8776_init(ice, &chip->wm[i], wm8776_addr[i]);
		wm8776_select_input(chip, i, MAYA_LINE_IN);
	}

	/* set card specific rates */
	ice->hw_rates = &dac_rates;

	/* register change rate notifier */
	ice->gpio.set_pro_rate = set_rate;

	/* RDMA1 (2nd input channel) is used for ADC by default */
	ice->force_rdma1 = 1;

	/* have an own routing control */
	ice->own_routing = 1;

	return 0;
}