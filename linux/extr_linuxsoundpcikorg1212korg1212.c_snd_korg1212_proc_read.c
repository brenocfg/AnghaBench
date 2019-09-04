#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_korg1212 {size_t clkSrcRate; size_t cardState; scalar_t__ totalerrorcnt; scalar_t__ irqcount; scalar_t__ cmdRetryCount; scalar_t__ idleMonitorOn; TYPE_2__* sharedBufferPtr; scalar_t__ rightADCInSens; scalar_t__ leftADCInSens; TYPE_1__* card; } ;
struct snd_info_entry {struct snd_korg1212* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct TYPE_4__ {size_t* routeData; scalar_t__ AdatTimeCode; int /*<<< orphan*/ * volumeData; } ;
struct TYPE_3__ {scalar_t__ number; int /*<<< orphan*/  longname; } ;

/* Variables and functions */
 scalar_t__ K1212_PERIOD_BYTES ; 
 int /*<<< orphan*/ * channelName ; 
 scalar_t__* clockSourceName ; 
 int kAudioChannels ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 scalar_t__* stateName ; 

__attribute__((used)) static void snd_korg1212_proc_read(struct snd_info_entry *entry,
				   struct snd_info_buffer *buffer)
{
	int n;
	struct snd_korg1212 *korg1212 = entry->private_data;

	snd_iprintf(buffer, korg1212->card->longname);
	snd_iprintf(buffer, " (index #%d)\n", korg1212->card->number + 1);
	snd_iprintf(buffer, "\nGeneral settings\n");
	snd_iprintf(buffer, "    period size: %zd bytes\n", K1212_PERIOD_BYTES);
	snd_iprintf(buffer, "     clock mode: %s\n", clockSourceName[korg1212->clkSrcRate] );
	snd_iprintf(buffer, "  left ADC Sens: %d\n", korg1212->leftADCInSens );
	snd_iprintf(buffer, " right ADC Sens: %d\n", korg1212->rightADCInSens );
        snd_iprintf(buffer, "    Volume Info:\n");
        for (n=0; n<kAudioChannels; n++)
                snd_iprintf(buffer, " Channel %d: %s -> %s [%d]\n", n,
                                    channelName[n],
                                    channelName[korg1212->sharedBufferPtr->routeData[n]],
                                    korg1212->sharedBufferPtr->volumeData[n]);
	snd_iprintf(buffer, "\nGeneral status\n");
        snd_iprintf(buffer, " ADAT Time Code: %d\n", korg1212->sharedBufferPtr->AdatTimeCode);
        snd_iprintf(buffer, "     Card State: %s\n", stateName[korg1212->cardState]);
        snd_iprintf(buffer, "Idle mon. State: %d\n", korg1212->idleMonitorOn);
        snd_iprintf(buffer, "Cmd retry count: %d\n", korg1212->cmdRetryCount);
        snd_iprintf(buffer, "      Irq count: %ld\n", korg1212->irqcount);
        snd_iprintf(buffer, "    Error count: %ld\n", korg1212->totalerrorcnt);
}