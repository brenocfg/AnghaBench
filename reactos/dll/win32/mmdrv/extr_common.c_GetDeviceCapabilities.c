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
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ MMRESULT ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DeviceType ;
typedef  scalar_t__ DWORD_PTR ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  CloseKernelDevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 scalar_t__ DeviceIoControl (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ErrorToMmResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ IOCTL_MIDI_GET_CAPABILITIES ; 
 scalar_t__ IOCTL_WAVE_GET_CAPABILITIES ; 
 scalar_t__ IsAuxDevice (int /*<<< orphan*/ ) ; 
 scalar_t__ IsMidiDevice (int /*<<< orphan*/ ) ; 
 scalar_t__ IsWaveDevice (int /*<<< orphan*/ ) ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ MMSYSERR_NOTSUPPORTED ; 
 scalar_t__ OpenKernelDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

DWORD
GetDeviceCapabilities(
    DeviceType device_type,
    UINT device_id,
    DWORD_PTR capabilities,
    DWORD capabilities_size)
{
    MMRESULT result;
    DWORD ioctl;
    HANDLE handle;
    DWORD bytes_returned;
    BOOL device_io_result;

    ASSERT(capabilities);

    /* Choose the right IOCTL for the job */

    if ( IsWaveDevice(device_type) )
        ioctl = IOCTL_WAVE_GET_CAPABILITIES;
    else if ( IsMidiDevice(device_type) )
        ioctl = IOCTL_MIDI_GET_CAPABILITIES;
    else if ( IsAuxDevice(device_type) )
        return MMSYSERR_NOTSUPPORTED; /* TODO */
    else
        return MMSYSERR_NOTSUPPORTED;

    result = OpenKernelDevice(device_type,
                              device_id,
                              GENERIC_READ,
                              &handle);

    if ( result != MMSYSERR_NOERROR )
    {
        DPRINT("Failed to open kernel device\n");
        return result;
    }

    device_io_result = DeviceIoControl(handle,
                                       ioctl,
                                       NULL,
                                       0,
                                       (LPVOID) capabilities,
                                       capabilities_size,
                                       &bytes_returned,
                                       NULL);

    /* Translate result */

    if ( device_io_result )
        result = MMSYSERR_NOERROR;
    else
        result = ErrorToMmResult(GetLastError());

    /* Clean up and return */

    CloseKernelDevice(handle);

    return result;
}