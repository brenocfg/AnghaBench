#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct snd_korg1212 {size_t cardState; scalar_t__ dsp_is_loaded; int /*<<< orphan*/  wait; TYPE_1__ dma_dsp; } ;

/* Variables and functions */
 int CARD_BOOT_TIMEOUT ; 
 int EBUSY ; 
 int HZ ; 
 int /*<<< orphan*/  K1212_DB_StartDSPDownload ; 
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*,int,...) ; 
 size_t K1212_STATE_DSP_IN_PROCESS ; 
 int /*<<< orphan*/  UpperWordSwap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_korg1212_OnDSPDownloadComplete (struct snd_korg1212*) ; 
 int snd_korg1212_Send1212Command (struct snd_korg1212*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_korg1212_setCardState (struct snd_korg1212*,size_t) ; 
 int /*<<< orphan*/ * stateName ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int snd_korg1212_downloadDSPCode(struct snd_korg1212 *korg1212)
{
	int rc;

        K1212_DEBUG_PRINTK("K1212_DEBUG: DSP download is starting... [%s]\n",
			   stateName[korg1212->cardState]);

        // ---------------------------------------------------------------
        // verify the state of the card before proceeding.
        // ---------------------------------------------------------------
        if (korg1212->cardState >= K1212_STATE_DSP_IN_PROCESS)
                return 1;

        snd_korg1212_setCardState(korg1212, K1212_STATE_DSP_IN_PROCESS);

        rc = snd_korg1212_Send1212Command(korg1212, K1212_DB_StartDSPDownload,
                                     UpperWordSwap(korg1212->dma_dsp.addr),
                                     0, 0, 0);
	if (rc)
		K1212_DEBUG_PRINTK("K1212_DEBUG: Start DSP Download RC = %d [%s]\n",
				   rc, stateName[korg1212->cardState]);

	korg1212->dsp_is_loaded = 0;
	wait_event_timeout(korg1212->wait, korg1212->dsp_is_loaded, HZ * CARD_BOOT_TIMEOUT);
	if (! korg1212->dsp_is_loaded )
		return -EBUSY; /* timeout */

	snd_korg1212_OnDSPDownloadComplete(korg1212);

        return 0;
}