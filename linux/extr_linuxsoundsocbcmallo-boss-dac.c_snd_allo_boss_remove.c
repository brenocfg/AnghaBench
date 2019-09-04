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
 int /*<<< orphan*/  snd_allo_boss ; 
 int /*<<< orphan*/  snd_allo_boss_gpio_mute (int /*<<< orphan*/ *) ; 
 int snd_soc_unregister_card (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_allo_boss_remove(struct platform_device *pdev)
{
	snd_allo_boss_gpio_mute(&snd_allo_boss);
	return snd_soc_unregister_card(&snd_allo_boss);
}