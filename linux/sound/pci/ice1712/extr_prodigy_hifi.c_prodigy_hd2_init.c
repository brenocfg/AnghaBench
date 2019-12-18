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
struct TYPE_2__ {scalar_t__* saved; } ;
struct snd_ice1712 {int vt1724; int num_total_dacs; int num_total_adcs; int akm_codecs; int pm_suspend_enabled; int /*<<< orphan*/ * pm_resume; struct prodigy_hifi_spec* spec; void* akm; TYPE_1__ gpio; scalar_t__ vt1720; } ;
struct snd_akm4xxx {int dummy; } ;
struct prodigy_hifi_spec {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ak4396_init (struct snd_ice1712*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prodigy_hd2_resume ; 

__attribute__((used)) static int prodigy_hd2_init(struct snd_ice1712 *ice)
{
	struct prodigy_hifi_spec *spec;

	ice->vt1720 = 0;
	ice->vt1724 = 1;

	ice->num_total_dacs = 1;
	ice->num_total_adcs = 1;

	/* HACK - use this as the SPDIF source.
	* don't call snd_ice1712_gpio_get/put(), otherwise it's overwritten
	*/
	ice->gpio.saved[0] = 0;
	/* to remember the register values */

	ice->akm = kzalloc(sizeof(struct snd_akm4xxx), GFP_KERNEL);
	if (! ice->akm)
		return -ENOMEM;
	ice->akm_codecs = 1;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	ice->spec = spec;

#ifdef CONFIG_PM_SLEEP
	ice->pm_resume = &prodigy_hd2_resume;
	ice->pm_suspend_enabled = 1;
#endif

	ak4396_init(ice);

	return 0;
}