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
struct device {int dummy; } ;

/* Variables and functions */
 int led_classdev_register (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mail_led ; 

__attribute__((used)) static int acer_led_init(struct device *dev)
{
	return led_classdev_register(dev, &mail_led);
}