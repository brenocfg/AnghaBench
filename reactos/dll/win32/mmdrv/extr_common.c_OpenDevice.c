#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int /*<<< orphan*/  dwInstance; int /*<<< orphan*/  hWave; int /*<<< orphan*/  dwCallback; } ;
struct TYPE_7__ {int /*<<< orphan*/  app_user_data; int /*<<< orphan*/  mme_wave_handle; int /*<<< orphan*/  callback; scalar_t__ flags; int /*<<< orphan*/  kernel_device_handle; } ;
typedef  TYPE_1__ SessionInfo ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ MMRESULT ;
typedef  TYPE_2__* LPWAVEOPENDESC ;
typedef  scalar_t__ DeviceType ;
typedef  scalar_t__ DWORD_PTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CreateSession (scalar_t__,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DestroySession (TYPE_1__*) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ IsWaveDevice (scalar_t__) ; 
 int MIM_OPEN ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ MMSYSERR_NOTSUPPORTED ; 
 int MOM_OPEN ; 
 scalar_t__ MidiInDevice ; 
 scalar_t__ MidiOutDevice ; 
 int /*<<< orphan*/  NotifyClient (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OpenKernelDevice (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ StartSessionThread (TYPE_1__*) ; 
 int WIM_OPEN ; 
 int WOM_OPEN ; 
 scalar_t__ WaveInDevice ; 
 scalar_t__ WaveOutDevice ; 

DWORD
OpenDevice(
    DeviceType device_type,
    UINT device_id,
    PVOID open_descriptor,
    DWORD flags,
    DWORD_PTR private_handle)
{
    SessionInfo* session_info;
    MMRESULT result;
    DWORD message;

    /* This will automatically check for duplicate sessions */
    result = CreateSession(device_type, device_id, &session_info);

    if ( result != MMSYSERR_NOERROR )
    {
        DPRINT("Couldn't allocate session info\n");
        return result;
    }

    result = OpenKernelDevice(device_type,
                              device_id,
                              GENERIC_READ,
                              &session_info->kernel_device_handle);

    if ( result != MMSYSERR_NOERROR )
    {
        DPRINT("Failed to open kernel device\n");
        DestroySession(session_info);
        return result;
    }

    /* Set common session data */

    session_info->flags = flags;

    /* Set wave/MIDI specific data */

    if ( IsWaveDevice(device_type) )
    {
        LPWAVEOPENDESC wave_open_desc = (LPWAVEOPENDESC) open_descriptor;
        session_info->callback = wave_open_desc->dwCallback;
        session_info->mme_wave_handle = wave_open_desc->hWave;
        session_info->app_user_data = wave_open_desc->dwInstance;
    }
    else
    {
        DPRINT("Only wave devices are supported at present!\n");
        DestroySession(session_info);
        return MMSYSERR_NOTSUPPORTED;
    }

    /* Start the processing thread */

    result = StartSessionThread(session_info);

    if ( result != MMSYSERR_NOERROR )
    {
        DestroySession(session_info);
        return result;
    }

    /* Store the session info */

    *((SessionInfo**)private_handle) = session_info;

    /* Send the right message */

    message = (device_type == WaveOutDevice) ? WOM_OPEN :
              (device_type == WaveInDevice) ? WIM_OPEN :
              (device_type == MidiOutDevice) ? MOM_OPEN :
              (device_type == MidiInDevice) ? MIM_OPEN : 0xFFFFFFFF;

    NotifyClient(session_info, message, 0, 0);

    return MMSYSERR_NOERROR;
}