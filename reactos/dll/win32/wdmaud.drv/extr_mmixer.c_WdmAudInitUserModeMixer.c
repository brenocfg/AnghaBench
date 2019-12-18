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
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ MIXER_STATUS ;
typedef  scalar_t__ HDEVINFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CategoryGuid ; 
 int /*<<< orphan*/  DIGCF_DEVICEINTERFACE ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  Enum ; 
 scalar_t__ FALSE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ MM_STATUS_SUCCESS ; 
 scalar_t__ MMixerInitialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MMixerLibraryInitialized ; 
 int /*<<< orphan*/  MixerContext ; 
 int /*<<< orphan*/  SetupDiDestroyDeviceInfoList (scalar_t__) ; 
 scalar_t__ SetupDiGetClassDevs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

BOOL
WdmAudInitUserModeMixer()
{
    HDEVINFO DeviceHandle;
    MIXER_STATUS Status;

    if (MMixerLibraryInitialized)
    {
        /* library is already initialized */
        return TRUE;
    }


    /* create a device list */
    DeviceHandle = SetupDiGetClassDevs(&CategoryGuid,
                                       NULL,
                                       NULL,
                                       DIGCF_DEVICEINTERFACE/* FIXME |DIGCF_PRESENT*/);

    if (DeviceHandle == INVALID_HANDLE_VALUE)
    {
        /* failed to create a device list */
        return FALSE;
    }


    /* initialize the mixer library */
    Status = MMixerInitialize(&MixerContext, Enum, (PVOID)DeviceHandle);

    /* free device list */
    SetupDiDestroyDeviceInfoList(DeviceHandle);

    if (Status != MM_STATUS_SUCCESS)
    {
        /* failed to initialize mixer library */
        DPRINT1("Failed to initialize mixer library with %x\n", Status);
        return FALSE;
    }

    /* library is now initialized */
    MMixerLibraryInitialized = TRUE;

    /* completed successfully */
    return TRUE;
}