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
struct snd_korg1212 {size_t cardState; scalar_t__ setcnt; scalar_t__ playcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ K1212_STATE_ERRORSTOP ; 
 int /*<<< orphan*/  K1212_STATE_OPEN ; 
 int /*<<< orphan*/  snd_korg1212_SendStop (struct snd_korg1212*) ; 
 int /*<<< orphan*/  snd_korg1212_setCardState (struct snd_korg1212*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stateName ; 

__attribute__((used)) static int snd_korg1212_StopPlay(struct snd_korg1212 * korg1212)
{
	K1212_DEBUG_PRINTK("K1212_DEBUG: StopPlay [%s] %d\n",
			   stateName[korg1212->cardState], korg1212->playcnt);

        if (--(korg1212->playcnt)) 
		return 0;

	korg1212->setcnt = 0;

        if (korg1212->cardState != K1212_STATE_ERRORSTOP)
		snd_korg1212_SendStop(korg1212);

	snd_korg1212_setCardState(korg1212, K1212_STATE_OPEN);
        return 0;
}