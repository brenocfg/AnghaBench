#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_9__ {int /*<<< orphan*/  hFilter; } ;
struct TYPE_8__ {int /*<<< orphan*/ * hPin; int /*<<< orphan*/  dwFrequency; TYPE_6__* Filter; } ;
struct TYPE_7__ {int /*<<< orphan*/  nSamplesPerSec; } ;
typedef  TYPE_1__* LPWAVEFORMATEX ;
typedef  int /*<<< orphan*/  LPDIRECTSOUNDBUFFER8 ;
typedef  TYPE_2__* LPCDirectSoundBuffer ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CDirectSoundBuffer ; 
 int /*<<< orphan*/  CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DSERR_GENERIC ; 
 int /*<<< orphan*/  DSERR_INVALIDPARAM ; 
 int /*<<< orphan*/  DS_OK ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetPinIdFromFilter (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ OpenPin (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ SetPinFormat (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  lpVtbl ; 

HRESULT
PrimaryDirectSoundBuffer_SetFormat(
    LPDIRECTSOUNDBUFFER8 iface,
    LPWAVEFORMATEX pcfxFormat,
    BOOL bLooped)
{
    ULONG PinId, DeviceId = 0, Result;
    LPCDirectSoundBuffer This = (LPCDirectSoundBuffer)CONTAINING_RECORD(iface, CDirectSoundBuffer, lpVtbl);

    if (This->hPin)
    {
        // FIXME
        // check if multiple buffers are active
        // in that case need mixing

        if (SetPinFormat(This->hPin, pcfxFormat))
            return DS_OK;
        else
            return DSERR_GENERIC;
    }

    do
    {
        /* try all available recording pins on that filter */
        PinId = GetPinIdFromFilter(This->Filter, FALSE, DeviceId);
        DPRINT("PinId %u DeviceId %u\n", PinId, DeviceId);

        if (PinId == ULONG_MAX)
            break;

        Result = OpenPin(This->Filter->hFilter, PinId, (LPWAVEFORMATEX)pcfxFormat, &This->hPin, bLooped);
        DPRINT("PinId %u Result %u\n", PinId, Result);
        if (Result == ERROR_SUCCESS)
        {
            This->dwFrequency = pcfxFormat->nSamplesPerSec;
            break;
        }

        This->hPin = NULL;
        DeviceId++;
    }while(TRUE);

    if (!This->hPin)
    {
        DPRINT("PrimaryDirectSoundBuffer8Impl_fnSetFormat failed\n");
        return DSERR_INVALIDPARAM;
    }

    DPRINT("PrimaryDirectSoundBuffer8Impl_fnSetFormat success\n");
    return DS_OK;
}