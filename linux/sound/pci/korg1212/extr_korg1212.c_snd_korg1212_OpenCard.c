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
struct snd_korg1212 {size_t cardState; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  opencnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  K1212_STATE_OPEN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_korg1212_TurnOffIdleMonitor (struct snd_korg1212*) ; 
 int /*<<< orphan*/  snd_korg1212_setCardState (struct snd_korg1212*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stateName ; 

__attribute__((used)) static int snd_korg1212_OpenCard(struct snd_korg1212 * korg1212)
{
	K1212_DEBUG_PRINTK("K1212_DEBUG: OpenCard [%s] %d\n",
			   stateName[korg1212->cardState], korg1212->opencnt);
	mutex_lock(&korg1212->open_mutex);
        if (korg1212->opencnt++ == 0) {
		snd_korg1212_TurnOffIdleMonitor(korg1212);
		snd_korg1212_setCardState(korg1212, K1212_STATE_OPEN);
	}

	mutex_unlock(&korg1212->open_mutex);
        return 1;
}