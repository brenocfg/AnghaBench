#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dwFlags; int dnDevNode; } ;
struct TYPE_5__ {int /*<<< orphan*/ * driver; int /*<<< orphan*/  pwfx; TYPE_3__ drvdesc; scalar_t__ hwo; int /*<<< orphan*/ * buffer; } ;
typedef  int /*<<< orphan*/  HWAVEOUT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DirectSoundDevice ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CALLBACK_FUNCTION ; 
 int /*<<< orphan*/  DRV_QUERYDSOUNDIFACE ; 
 int DSDDESC_DOMMSYSTEMOPEN ; 
 int DSDDESC_DOMMSYSTEMSETFORMAT ; 
 scalar_t__ DSOUND_callback ; 
 scalar_t__ DS_HW_ACCEL_EMULATION ; 
 int /*<<< orphan*/  DS_OK ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDsDriver_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDsDriver_GetDriverDesc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  IDsDriver_Open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDsDriver_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int WAVE_DIRECTSOUND ; 
 int WAVE_MAPPED ; 
 scalar_t__ ds_hw_accel ; 
 int /*<<< orphan*/  mmErr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waveOutClose (scalar_t__) ; 
 int /*<<< orphan*/  waveOutMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waveOutOpen (scalar_t__*,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 

HRESULT DSOUND_ReopenDevice(DirectSoundDevice *device, BOOL forcewave)
{
	HRESULT hres = DS_OK;
	TRACE("(%p, %d)\n", device, forcewave);

	if (device->driver)
	{
		IDsDriver_Close(device->driver);
		if (device->drvdesc.dwFlags & DSDDESC_DOMMSYSTEMOPEN)
			waveOutClose(device->hwo);
		IDsDriver_Release(device->driver);
		device->driver = NULL;
		device->buffer = NULL;
		device->hwo = 0;
	}
	else if (device->drvdesc.dwFlags & DSDDESC_DOMMSYSTEMOPEN)
		waveOutClose(device->hwo);

	/* DRV_QUERYDSOUNDIFACE is a "Wine extension" to get the DSound interface */
	if (ds_hw_accel != DS_HW_ACCEL_EMULATION && !forcewave)
		waveOutMessage((HWAVEOUT)(DWORD_PTR)device->drvdesc.dnDevNode, DRV_QUERYDSOUNDIFACE, (DWORD_PTR)&device->driver, 0);

	/* Get driver description */
	if (device->driver) {
		DWORD wod = device->drvdesc.dnDevNode;
		hres = IDsDriver_GetDriverDesc(device->driver,&(device->drvdesc));
		device->drvdesc.dnDevNode = wod;
		if (FAILED(hres)) {
			WARN("IDsDriver_GetDriverDesc failed: %08x\n", hres);
			IDsDriver_Release(device->driver);
			device->driver = NULL;
		}
        }

        /* if no DirectSound interface available, use WINMM API instead */
	if (!device->driver)
		device->drvdesc.dwFlags = DSDDESC_DOMMSYSTEMOPEN | DSDDESC_DOMMSYSTEMSETFORMAT;

	if (device->drvdesc.dwFlags & DSDDESC_DOMMSYSTEMOPEN)
	{
		DWORD flags = CALLBACK_FUNCTION | WAVE_MAPPED;

		if (device->driver)
			flags |= WAVE_DIRECTSOUND;

		hres = mmErr(waveOutOpen(&(device->hwo), device->drvdesc.dnDevNode, device->pwfx, (DWORD_PTR)DSOUND_callback, (DWORD_PTR)device, flags));
		if (FAILED(hres)) {
			WARN("waveOutOpen failed\n");
			if (device->driver)
			{
				IDsDriver_Release(device->driver);
				device->driver = NULL;
			}
			return hres;
		}
	}

	if (device->driver)
		hres = IDsDriver_Open(device->driver);

	return hres;
}