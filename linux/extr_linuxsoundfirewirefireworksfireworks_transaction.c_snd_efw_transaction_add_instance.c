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
struct snd_efw {int dummy; } ;

/* Variables and functions */
 unsigned int SNDRV_CARDS ; 
 struct snd_efw** instances ; 
 int /*<<< orphan*/  instances_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void snd_efw_transaction_add_instance(struct snd_efw *efw)
{
	unsigned int i;

	spin_lock_irq(&instances_lock);

	for (i = 0; i < SNDRV_CARDS; i++) {
		if (instances[i] != NULL)
			continue;
		instances[i] = efw;
		break;
	}

	spin_unlock_irq(&instances_lock);
}