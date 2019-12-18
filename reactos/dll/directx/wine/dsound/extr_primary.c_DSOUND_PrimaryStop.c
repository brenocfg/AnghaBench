#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mixlock; int /*<<< orphan*/  hwo; scalar_t__ hwbuf; } ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ DirectSoundDevice ;

/* Variables and functions */
 scalar_t__ DSERR_BUFFERLOST ; 
 int /*<<< orphan*/  DSOUND_PrimaryClose (TYPE_1__*) ; 
 scalar_t__ DSOUND_PrimaryOpen (TYPE_1__*) ; 
 scalar_t__ DSOUND_ReopenDevice (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ DS_OK ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDsDriverBuffer_Stop (scalar_t__) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ mmErr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waveOutPause (int /*<<< orphan*/ ) ; 

HRESULT DSOUND_PrimaryStop(DirectSoundDevice *device)
{
	HRESULT err = DS_OK;
	TRACE("(%p)\n", device);

	if (device->hwbuf) {
		err = IDsDriverBuffer_Stop(device->hwbuf);
		if (err == DSERR_BUFFERLOST) {
			DSOUND_PrimaryClose(device);
			err = DSOUND_ReopenDevice(device, FALSE);
			if (FAILED(err))
				ERR("DSOUND_ReopenDevice failed\n");
			else
			{
				err = DSOUND_PrimaryOpen(device);
				if (FAILED(err))
					WARN("DSOUND_PrimaryOpen failed\n");
			}
		} else if (err != DS_OK) {
			WARN("IDsDriverBuffer_Stop failed\n");
		}
	} else {

		/* don't call the wave system with the lock set */
		LeaveCriticalSection(&(device->mixlock));
		/* **** */

		err = mmErr(waveOutPause(device->hwo));

		/* **** */
		EnterCriticalSection(&(device->mixlock));

		if (err != DS_OK)
			WARN("waveOutPause failed\n");
	}

	return err;
}