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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct phy_led_trigger {unsigned int speed; TYPE_1__ trigger; int /*<<< orphan*/  name; } ;
struct phy_device {int dummy; } ;
typedef  int /*<<< orphan*/  name_suffix ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int PHY_LED_TRIGGER_SPEED_SUFFIX_SIZE ; 
 unsigned int SPEED_1000 ; 
 unsigned int SPEED_2500 ; 
 int led_trigger_register (TYPE_1__*) ; 
 int /*<<< orphan*/  phy_led_trigger_format_name (struct phy_device*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int phy_led_trigger_register(struct phy_device *phy,
				    struct phy_led_trigger *plt,
				    unsigned int speed)
{
	char name_suffix[PHY_LED_TRIGGER_SPEED_SUFFIX_SIZE];

	plt->speed = speed;

	if (speed < SPEED_1000)
		snprintf(name_suffix, sizeof(name_suffix), "%dMbps", speed);
	else if (speed == SPEED_2500)
		snprintf(name_suffix, sizeof(name_suffix), "2.5Gbps");
	else
		snprintf(name_suffix, sizeof(name_suffix), "%dGbps",
			 DIV_ROUND_CLOSEST(speed, 1000));

	phy_led_trigger_format_name(phy, plt->name, sizeof(plt->name),
				    name_suffix);
	plt->trigger.name = plt->name;

	return led_trigger_register(&plt->trigger);
}