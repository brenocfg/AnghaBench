#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_pmac {scalar_t__ model; void* master_sw_ctl; void* speaker_sw_ctl; void* lineout_sw_ctl; void* drc_sw_ctl; TYPE_4__* card; TYPE_1__* node; int /*<<< orphan*/  mixer_free; struct pmac_tumbler* mixer_data; } ;
struct TYPE_6__ {scalar_t__ addr; } ;
struct TYPE_7__ {int addr; char* name; int /*<<< orphan*/  init_client; } ;
struct pmac_tumbler {int headphone_irq; int anded_reset; int reset_on_sleep; int drc_range; int drc_enable; TYPE_2__ line_mute; TYPE_3__ i2c; } ;
struct device_node {int /*<<< orphan*/  name; struct device_node* sibling; } ;
struct TYPE_8__ {int /*<<< orphan*/  mixername; } ;
struct TYPE_5__ {struct device_node* child; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DBG (char*,int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PMAC_TUMBLER ; 
 int TAS3001_DRC_MAX ; 
 int TAS3004_DRC_MAX ; 
 int TAS_I2C_ADDR ; 
 int /*<<< orphan*/  device_change ; 
 struct snd_pmac* device_change_chip ; 
 int /*<<< orphan*/  device_change_handler ; 
 struct pmac_tumbler* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  request_module (char*) ; 
 int /*<<< orphan*/  snapper_init_client ; 
 int /*<<< orphan*/ * snapper_mixers ; 
 int /*<<< orphan*/  snapper_set_drc (struct pmac_tumbler*) ; 
 int snd_ctl_add (TYPE_4__*,void*) ; 
 void* snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_pmac*) ; 
 int snd_pmac_keywest_init (TYPE_3__*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tumbler_cleanup ; 
 int /*<<< orphan*/  tumbler_drc_sw ; 
 int /*<<< orphan*/  tumbler_hp_sw ; 
 int tumbler_init (struct snd_pmac*) ; 
 int /*<<< orphan*/  tumbler_init_client ; 
 int /*<<< orphan*/  tumbler_lineout_sw ; 
 int /*<<< orphan*/ * tumbler_mixers ; 
 int /*<<< orphan*/  tumbler_set_drc (struct pmac_tumbler*) ; 
 int /*<<< orphan*/  tumbler_speaker_sw ; 

int snd_pmac_tumbler_init(struct snd_pmac *chip)
{
	int i, err;
	struct pmac_tumbler *mix;
	const u32 *paddr;
	struct device_node *tas_node, *np;
	char *chipname;

	request_module("i2c-powermac");

	mix = kzalloc(sizeof(*mix), GFP_KERNEL);
	if (! mix)
		return -ENOMEM;
	mix->headphone_irq = -1;

	chip->mixer_data = mix;
	chip->mixer_free = tumbler_cleanup;
	mix->anded_reset = 0;
	mix->reset_on_sleep = 1;

	for (np = chip->node->child; np; np = np->sibling) {
		if (!strcmp(np->name, "sound")) {
			if (of_get_property(np, "has-anded-reset", NULL))
				mix->anded_reset = 1;
			if (of_get_property(np, "layout-id", NULL))
				mix->reset_on_sleep = 0;
			break;
		}
	}
	if ((err = tumbler_init(chip)) < 0)
		return err;

	/* set up TAS */
	tas_node = of_find_node_by_name(NULL, "deq");
	if (tas_node == NULL)
		tas_node = of_find_node_by_name(NULL, "codec");
	if (tas_node == NULL)
		return -ENODEV;

	paddr = of_get_property(tas_node, "i2c-address", NULL);
	if (paddr == NULL)
		paddr = of_get_property(tas_node, "reg", NULL);
	if (paddr)
		mix->i2c.addr = (*paddr) >> 1;
	else
		mix->i2c.addr = TAS_I2C_ADDR;
	of_node_put(tas_node);

	DBG("(I) TAS i2c address is: %x\n", mix->i2c.addr);

	if (chip->model == PMAC_TUMBLER) {
		mix->i2c.init_client = tumbler_init_client;
		mix->i2c.name = "TAS3001c";
		chipname = "Tumbler";
	} else {
		mix->i2c.init_client = snapper_init_client;
		mix->i2c.name = "TAS3004";
		chipname = "Snapper";
	}

	if ((err = snd_pmac_keywest_init(&mix->i2c)) < 0)
		return err;

	/*
	 * build mixers
	 */
	sprintf(chip->card->mixername, "PowerMac %s", chipname);

	if (chip->model == PMAC_TUMBLER) {
		for (i = 0; i < ARRAY_SIZE(tumbler_mixers); i++) {
			if ((err = snd_ctl_add(chip->card, snd_ctl_new1(&tumbler_mixers[i], chip))) < 0)
				return err;
		}
	} else {
		for (i = 0; i < ARRAY_SIZE(snapper_mixers); i++) {
			if ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snapper_mixers[i], chip))) < 0)
				return err;
		}
	}
	chip->master_sw_ctl = snd_ctl_new1(&tumbler_hp_sw, chip);
	if ((err = snd_ctl_add(chip->card, chip->master_sw_ctl)) < 0)
		return err;
	chip->speaker_sw_ctl = snd_ctl_new1(&tumbler_speaker_sw, chip);
	if ((err = snd_ctl_add(chip->card, chip->speaker_sw_ctl)) < 0)
		return err;
	if (mix->line_mute.addr != 0) {
		chip->lineout_sw_ctl = snd_ctl_new1(&tumbler_lineout_sw, chip);
		if ((err = snd_ctl_add(chip->card, chip->lineout_sw_ctl)) < 0)
			return err;
	}
	chip->drc_sw_ctl = snd_ctl_new1(&tumbler_drc_sw, chip);
	if ((err = snd_ctl_add(chip->card, chip->drc_sw_ctl)) < 0)
		return err;

	/* set initial DRC range to 60% */
	if (chip->model == PMAC_TUMBLER)
		mix->drc_range = (TAS3001_DRC_MAX * 6) / 10;
	else
		mix->drc_range = (TAS3004_DRC_MAX * 6) / 10;
	mix->drc_enable = 1; /* will be changed later if AUTO_DRC is set */
	if (chip->model == PMAC_TUMBLER)
		tumbler_set_drc(mix);
	else
		snapper_set_drc(mix);

#ifdef CONFIG_PM
	chip->suspend = tumbler_suspend;
	chip->resume = tumbler_resume;
#endif

	INIT_WORK(&device_change, device_change_handler);
	device_change_chip = chip;

#ifdef PMAC_SUPPORT_AUTOMUTE
	if ((mix->headphone_irq >=0 || mix->lineout_irq >= 0)
	    && (err = snd_pmac_add_automute(chip)) < 0)
		return err;
	chip->detect_headphone = tumbler_detect_headphone;
	chip->update_automute = tumbler_update_automute;
	tumbler_update_automute(chip, 0); /* update the status only */

	/* activate headphone status interrupts */
  	if (mix->headphone_irq >= 0) {
		unsigned char val;
		if ((err = request_irq(mix->headphone_irq, headphone_intr, 0,
				       "Sound Headphone Detection", chip)) < 0)
			return 0;
		/* activate headphone status interrupts */
		val = do_gpio_read(&mix->hp_detect);
		do_gpio_write(&mix->hp_detect, val | 0x80);
	}
  	if (mix->lineout_irq >= 0) {
		unsigned char val;
		if ((err = request_irq(mix->lineout_irq, headphone_intr, 0,
				       "Sound Lineout Detection", chip)) < 0)
			return 0;
		/* activate headphone status interrupts */
		val = do_gpio_read(&mix->line_detect);
		do_gpio_write(&mix->line_detect, val | 0x80);
	}
#endif

	return 0;
}