#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  set_pro_rate; } ;
struct snd_ice1712 {int num_total_dacs; int num_total_adcs; int pm_suspend_enabled; TYPE_3__ gpio; int /*<<< orphan*/  pm_resume; int /*<<< orphan*/  card; struct psc724_spec* spec; } ;
struct TYPE_8__ {int /*<<< orphan*/  write; } ;
struct TYPE_11__ {int /*<<< orphan*/  card; TYPE_2__ ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  write; } ;
struct TYPE_10__ {int /*<<< orphan*/  card; TYPE_1__ ops; } ;
struct psc724_spec {int /*<<< orphan*/  hp_work; TYPE_5__ wm8766; TYPE_4__ wm8776; struct snd_ice1712* ice; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int WM8766_IF_FMT_I2S ; 
 int WM8766_IF_IWL_24BIT ; 
 struct psc724_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psc724_resume ; 
 int /*<<< orphan*/  psc724_set_jack_detection (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  psc724_set_pro_rate ; 
 int /*<<< orphan*/  psc724_update_hp_jack_state ; 
 int /*<<< orphan*/  psc724_wm8766_write ; 
 int /*<<< orphan*/  psc724_wm8776_write ; 
 int /*<<< orphan*/  snd_wm8766_init (TYPE_5__*) ; 
 int /*<<< orphan*/  snd_wm8766_set_if (TYPE_5__*,int) ; 
 int /*<<< orphan*/  snd_wm8776_init (TYPE_4__*) ; 

__attribute__((used)) static int psc724_init(struct snd_ice1712 *ice)
{
	struct psc724_spec *spec;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	ice->spec = spec;
	spec->ice = ice;

	ice->num_total_dacs = 6;
	ice->num_total_adcs = 2;
	spec->wm8776.ops.write = psc724_wm8776_write;
	spec->wm8776.card = ice->card;
	snd_wm8776_init(&spec->wm8776);
	spec->wm8766.ops.write = psc724_wm8766_write;
	spec->wm8766.card = ice->card;
#ifdef CONFIG_PM_SLEEP
	ice->pm_resume = psc724_resume;
	ice->pm_suspend_enabled = 1;
#endif
	snd_wm8766_init(&spec->wm8766);
	snd_wm8766_set_if(&spec->wm8766,
			WM8766_IF_FMT_I2S | WM8766_IF_IWL_24BIT);
	ice->gpio.set_pro_rate = psc724_set_pro_rate;
	INIT_DELAYED_WORK(&spec->hp_work, psc724_update_hp_jack_state);
	psc724_set_jack_detection(ice, true);
	return 0;
}