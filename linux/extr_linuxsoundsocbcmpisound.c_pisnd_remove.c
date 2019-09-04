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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pisnd_card ; 
 int /*<<< orphan*/ * pisnd_kobj ; 
 int /*<<< orphan*/  pisnd_spi_uninit () ; 
 int /*<<< orphan*/  pisnd_uninit_gpio () ; 
 int /*<<< orphan*/  printi (char*) ; 
 int /*<<< orphan*/  reset ; 
 int snd_soc_unregister_card (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pisnd_remove(struct platform_device *pdev)
{
	printi("Unloading.\n");

	if (pisnd_kobj) {
		kobject_put(pisnd_kobj);
		pisnd_kobj = NULL;
	}

	pisnd_spi_uninit();

	/* Turn off */
	gpiod_set_value(reset, false);
	pisnd_uninit_gpio();

	return snd_soc_unregister_card(&pisnd_card);
}