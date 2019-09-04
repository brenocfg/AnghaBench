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
struct nvec_chip {int /*<<< orphan*/  gpiod; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nvec_gpio_set_value(struct nvec_chip *nvec, int value)
{
	dev_dbg(nvec->dev, "GPIO changed from %u to %u\n",
		gpiod_get_value(nvec->gpiod), value);
	gpiod_set_value(nvec->gpiod, value);
}