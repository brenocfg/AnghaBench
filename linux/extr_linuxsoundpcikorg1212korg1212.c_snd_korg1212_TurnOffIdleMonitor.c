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
struct snd_korg1212 {scalar_t__ idleMonitorOn; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_korg1212_SendStopAndWait (struct snd_korg1212*) ; 

__attribute__((used)) static void snd_korg1212_TurnOffIdleMonitor(struct snd_korg1212 *korg1212)
{
        if (korg1212->idleMonitorOn) {
		snd_korg1212_SendStopAndWait(korg1212);
                korg1212->idleMonitorOn = 0;
        }
}