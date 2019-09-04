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
struct snd_korg1212 {size_t cardState; int opencnt; int /*<<< orphan*/  open_mutex; } ;

/* Variables and functions */
 int K1212_CMDRET_Success ; 
 int /*<<< orphan*/  K1212_DB_SelectPlayMode ; 
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*,int,int) ; 
 int /*<<< orphan*/  K1212_MODE_StopPlay ; 
 size_t K1212_STATE_READY ; 
 size_t K1212_STATE_SETUP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_korg1212_Send1212Command (struct snd_korg1212*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_korg1212_SendStopAndWait (struct snd_korg1212*) ; 
 int /*<<< orphan*/  snd_korg1212_TurnOnIdleMonitor (struct snd_korg1212*) ; 
 int /*<<< orphan*/  snd_korg1212_setCardState (struct snd_korg1212*,size_t) ; 
 int* stateName ; 

__attribute__((used)) static int snd_korg1212_CloseCard(struct snd_korg1212 * korg1212)
{
	K1212_DEBUG_PRINTK("K1212_DEBUG: CloseCard [%s] %d\n",
			   stateName[korg1212->cardState], korg1212->opencnt);

	mutex_lock(&korg1212->open_mutex);
	if (--(korg1212->opencnt)) {
		mutex_unlock(&korg1212->open_mutex);
		return 0;
	}

        if (korg1212->cardState == K1212_STATE_SETUP) {
                int rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_SelectPlayMode,
                                K1212_MODE_StopPlay, 0, 0, 0);
		if (rc)
			K1212_DEBUG_PRINTK("K1212_DEBUG: CloseCard - RC = %d [%s]\n",
					   rc, stateName[korg1212->cardState]);
		if (rc != K1212_CMDRET_Success) {
			mutex_unlock(&korg1212->open_mutex);
                        return 0;
		}
        } else if (korg1212->cardState > K1212_STATE_SETUP) {
		snd_korg1212_SendStopAndWait(korg1212);
        }

        if (korg1212->cardState > K1212_STATE_READY) {
		snd_korg1212_TurnOnIdleMonitor(korg1212);
                snd_korg1212_setCardState(korg1212, K1212_STATE_READY);
	}

	mutex_unlock(&korg1212->open_mutex);
        return 0;
}