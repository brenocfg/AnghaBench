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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct cs42l52_private {int /*<<< orphan*/ * beep; int /*<<< orphan*/  beep_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS42L52_BEEP_EN_MASK ; 
 int /*<<< orphan*/  CS42L52_BEEP_TONE_CTL ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_beep ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cs42l52_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs42l52_free_beep(struct snd_soc_component *component)
{
	struct cs42l52_private *cs42l52 = snd_soc_component_get_drvdata(component);

	device_remove_file(component->dev, &dev_attr_beep);
	cancel_work_sync(&cs42l52->beep_work);
	cs42l52->beep = NULL;

	snd_soc_component_update_bits(component, CS42L52_BEEP_TONE_CTL,
			    CS42L52_BEEP_EN_MASK, 0);
}