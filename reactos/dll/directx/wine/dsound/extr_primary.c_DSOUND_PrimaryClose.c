#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WAVEHDR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {unsigned int helfrags; scalar_t__ hwbuf; scalar_t__ pwqueue; int /*<<< orphan*/  mixlock; int /*<<< orphan*/ * pwave; int /*<<< orphan*/  hwo; } ;
typedef  TYPE_1__ DirectSoundDevice ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDsDriverBuffer_Release (scalar_t__) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  waveOutReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waveOutUnprepareHeader (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void DSOUND_PrimaryClose(DirectSoundDevice *device)
{
	TRACE("(%p)\n", device);

	/* are we using waveOut stuff? */
	if (!device->hwbuf) {
		unsigned c;

		/* get out of CS when calling the wave system */
		LeaveCriticalSection(&(device->mixlock));
		/* **** */
		device->pwqueue = (DWORD)-1; /* resetting queues */
		waveOutReset(device->hwo);
		for (c=0; c<device->helfrags; c++)
			waveOutUnprepareHeader(device->hwo, &device->pwave[c], sizeof(WAVEHDR));
		/* **** */
		EnterCriticalSection(&(device->mixlock));

		/* clear the queue */
		device->pwqueue = 0;
	} else {
		ULONG ref = IDsDriverBuffer_Release(device->hwbuf);
		if (!ref)
			device->hwbuf = 0;
		else
			ERR("Still %d references on primary buffer, refcount leak?\n", ref);
	}
}