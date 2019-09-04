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
struct TYPE_2__ {scalar_t__ type; } ;
struct rt2x00_dev {TYPE_1__ led_qual; } ;

/* Variables and functions */
 scalar_t__ LED_TYPE_ACTIVITY ; 
 int /*<<< orphan*/  rt2x00led_led_simple (TYPE_1__*,int) ; 

void rt2x00led_led_activity(struct rt2x00_dev *rt2x00dev, bool enabled)
{
	if (rt2x00dev->led_qual.type == LED_TYPE_ACTIVITY)
		rt2x00led_led_simple(&rt2x00dev->led_qual, enabled);
}