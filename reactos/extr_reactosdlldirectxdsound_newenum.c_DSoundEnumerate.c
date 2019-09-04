#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* szPname; } ;
typedef  TYPE_1__ WAVEOUTCAPSW ;
typedef  TYPE_1__ WAVEINCAPSW ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  UINT_PTR ;
struct TYPE_10__ {scalar_t__* MappedId; struct TYPE_10__* lpNext; int /*<<< orphan*/ * DeviceGuid; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_3__* LPFILTERINFO ;
typedef  int /*<<< orphan*/ * LPDSENUMCALLBACKW ;
typedef  int /*<<< orphan*/ * LPDSENUMCALLBACKA ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DSERR_INVALIDPARAM ; 
 int /*<<< orphan*/  DS_OK ; 
 scalar_t__ DoDSoundCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnumAudioDeviceInterfaces (TYPE_3__**) ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  IDS_PRIMARY_PLAYBACK_DEVICE ; 
 int /*<<< orphan*/  IDS_PRIMARY_RECORD_DEVICE ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAXPNAMELEN ; 
 TYPE_3__* RootInfo ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  waveInGetDevCapsW (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  waveOutGetDevCapsW (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

HRESULT
DSoundEnumerate(
    LPDSENUMCALLBACKA lpDSEnumCallbackA,
    LPDSENUMCALLBACKW lpDSEnumCallbackW,
    LPVOID lpContext,
    BOOL bPlayback)
{
    ULONG ResourceId;
    BOOL bResult;
    LPFILTERINFO CurInfo;
    WAVEOUTCAPSW WaveOutCaps;
    WAVEINCAPSW  WaveInCaps;

    if (!RootInfo)
    {
        EnumAudioDeviceInterfaces(&RootInfo);
    }

    if (lpDSEnumCallbackA == NULL && lpDSEnumCallbackW == NULL)
    {
        DPRINT("No callback\n");
        return DSERR_INVALIDPARAM;
    }

    if (bPlayback)
    {
        /* use resource id of playback string */
        ResourceId = IDS_PRIMARY_PLAYBACK_DEVICE;
    }
    else
    {
        /* use resource id of playback string */
        ResourceId = IDS_PRIMARY_RECORD_DEVICE;
    }

    if (RootInfo)
    {
        /* perform first callback */
        bResult = DoDSoundCallback(lpDSEnumCallbackA, lpDSEnumCallbackW, NULL, ResourceId, NULL, L"", lpContext);
        if (!bResult)
        {
            /* callback asked as to stop */
            return DS_OK;
        }

        /* now iterate through all devices */
        CurInfo = RootInfo;

        do
        {
            if (bPlayback && !IsEqualGUID(&CurInfo->DeviceGuid[1], &GUID_NULL))
            {
                RtlZeroMemory(&WaveOutCaps, sizeof(WAVEOUTCAPSW));

                /* sanity check */
                ASSERT(CurInfo->MappedId[1] != ULONG_MAX);

                /* get wave out caps */
                waveOutGetDevCapsW((UINT_PTR)CurInfo->MappedId[1], &WaveOutCaps, sizeof(WAVEOUTCAPSW));
                WaveOutCaps.szPname[MAXPNAMELEN-1] = L'\0';

                bResult = DoDSoundCallback(lpDSEnumCallbackA, lpDSEnumCallbackW, &CurInfo->DeviceGuid[1], 0, WaveOutCaps.szPname, L"" /* FIXME */, lpContext);
                if (!bResult)
                {
                    /* callback asked as to stop */
                    return DS_OK;
                }
            }
            else if (!bPlayback && !IsEqualGUID(&CurInfo->DeviceGuid[0], &GUID_NULL))
            {
                RtlZeroMemory(&WaveInCaps, sizeof(WAVEINCAPSW));

                /* sanity check */
                ASSERT(CurInfo->MappedId[1] != ULONG_MAX);

                /* get wave in caps */
                waveInGetDevCapsW((UINT_PTR)CurInfo->MappedId[0], &WaveInCaps, sizeof(WAVEINCAPSW));
                WaveInCaps.szPname[MAXPNAMELEN-1] = L'\0';

                bResult = DoDSoundCallback(lpDSEnumCallbackA, lpDSEnumCallbackW, &CurInfo->DeviceGuid[0], 0, WaveInCaps.szPname, L"" /* FIXME */, lpContext);
                if (!bResult)
                {
                    /* callback asked as to stop */
                    return DS_OK;
                }
            }

            /* move to next entry */
            CurInfo = CurInfo->lpNext;
        }while(CurInfo);
    }
    return DS_OK;
}