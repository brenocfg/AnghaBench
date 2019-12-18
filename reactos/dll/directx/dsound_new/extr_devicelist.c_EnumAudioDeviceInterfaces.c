#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {struct TYPE_9__* lpNext; } ;
typedef  TYPE_1__* LPFILTERINFO ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HDEVINFO ;
typedef  TYPE_2__ GUID ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  CloseDeviceList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ EnumerateAudioFilter (TYPE_1__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  GetDeviceListInterfaces (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__**) ; 
 scalar_t__ OpenDeviceList (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATIC_KSCATEGORY_AUDIO ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 

HRESULT
EnumAudioDeviceInterfaces(
    LPFILTERINFO *OutRootInfo)
{
    HDEVINFO hList;
    DWORD Status;
    HRESULT hResult;
    ULONG WaveOutCount, WaveInCount;
    GUID AudioDeviceGuid = {STATIC_KSCATEGORY_AUDIO};
    LPFILTERINFO CurInfo;

    /* try open the device list */
    Status = OpenDeviceList(&AudioDeviceGuid, &hList);

    if (Status != ERROR_SUCCESS)
    {
        DPRINT1("OpenDeviceList failed with %lx\n", Status);
        return E_FAIL;
    }

    if (!GetDeviceListInterfaces(hList, &AudioDeviceGuid, OutRootInfo))
    {
        DPRINT1("No devices found\n");
        CloseDeviceList(hList);
        return S_FALSE;
    }

    /* sanity check */
    ASSERT(*OutRootInfo);

    CurInfo = *OutRootInfo;

    WaveOutCount = 0;
    WaveInCount = 0;

    /* now check all audio filters */
    while(CurInfo)
    {
        /* now check details of the audio filter */
        hResult = EnumerateAudioFilter(CurInfo, &WaveInCount, &WaveOutCount);

        if (hResult != S_OK)
        {
           DPRINT1("EnumerateAudioFilter failed with %lx\n", Status);
           break;
        }

        /* move to next filter */
        CurInfo = CurInfo->lpNext;
    }

    /* close device list */
    CloseDeviceList(hList);

    /* done */
    return hResult;
}