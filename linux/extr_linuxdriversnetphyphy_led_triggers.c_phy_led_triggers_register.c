#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct phy_led_trigger {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct phy_device {int phy_num_led_triggers; TYPE_2__* led_link_trigger; TYPE_1__ mdio; TYPE_2__* phy_led_triggers; int /*<<< orphan*/ * last_triggered; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_4__ trigger; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned int*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int led_trigger_register (TYPE_4__*) ; 
 int /*<<< orphan*/  phy_led_trigger_change_speed (struct phy_device*) ; 
 int /*<<< orphan*/  phy_led_trigger_format_name (struct phy_device*,int /*<<< orphan*/ ,int,char*) ; 
 int phy_led_trigger_register (struct phy_device*,TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  phy_led_trigger_unregister (TYPE_2__*) ; 
 int phy_supported_speeds (struct phy_device*,unsigned int*,int /*<<< orphan*/ ) ; 

int phy_led_triggers_register(struct phy_device *phy)
{
	int i, err;
	unsigned int speeds[50];

	phy->phy_num_led_triggers = phy_supported_speeds(phy, speeds,
							 ARRAY_SIZE(speeds));
	if (!phy->phy_num_led_triggers)
		return 0;

	phy->led_link_trigger = devm_kzalloc(&phy->mdio.dev,
					     sizeof(*phy->led_link_trigger),
					     GFP_KERNEL);
	if (!phy->led_link_trigger) {
		err = -ENOMEM;
		goto out_clear;
	}

	phy_led_trigger_format_name(phy, phy->led_link_trigger->name,
				    sizeof(phy->led_link_trigger->name),
				    "link");
	phy->led_link_trigger->trigger.name = phy->led_link_trigger->name;

	err = led_trigger_register(&phy->led_link_trigger->trigger);
	if (err)
		goto out_free_link;

	phy->phy_led_triggers = devm_kcalloc(&phy->mdio.dev,
					    phy->phy_num_led_triggers,
					    sizeof(struct phy_led_trigger),
					    GFP_KERNEL);
	if (!phy->phy_led_triggers) {
		err = -ENOMEM;
		goto out_unreg_link;
	}

	for (i = 0; i < phy->phy_num_led_triggers; i++) {
		err = phy_led_trigger_register(phy, &phy->phy_led_triggers[i],
					       speeds[i]);
		if (err)
			goto out_unreg;
	}

	phy->last_triggered = NULL;
	phy_led_trigger_change_speed(phy);

	return 0;
out_unreg:
	while (i--)
		phy_led_trigger_unregister(&phy->phy_led_triggers[i]);
	devm_kfree(&phy->mdio.dev, phy->phy_led_triggers);
out_unreg_link:
	phy_led_trigger_unregister(phy->led_link_trigger);
out_free_link:
	devm_kfree(&phy->mdio.dev, phy->led_link_trigger);
	phy->led_link_trigger = NULL;
out_clear:
	phy->phy_num_led_triggers = 0;
	return err;
}