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
struct snd_ac97 {int /*<<< orphan*/  dev; int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_ac97_free_gpio (struct snd_ac97*) ; 

void snd_soc_free_ac97_component(struct snd_ac97 *ac97)
{
	snd_soc_ac97_free_gpio(ac97);
	device_del(&ac97->dev);
	ac97->bus = NULL;
	put_device(&ac97->dev);
}