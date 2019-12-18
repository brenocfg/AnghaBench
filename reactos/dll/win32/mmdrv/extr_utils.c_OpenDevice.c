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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/ ***** PHANDLE ;
typedef  int /*<<< orphan*/  MMRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ AUX_DEVICE_NAME_U ; 
#define  AuxDevice 132 
 int /*<<< orphan*/ **** CreateFile (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  FILE_FLAG_OVERLAPPED ; 
 int /*<<< orphan*/  FILE_SHARE_WRITE ; 
 scalar_t__ GENERIC_READ ; 
 int /*<<< orphan*/ ***** INVALID_HANDLE_VALUE ; 
 scalar_t__ MIDI_IN_DEVICE_NAME_U ; 
 scalar_t__ MIDI_OUT_DEVICE_NAME_U ; 
 int /*<<< orphan*/  MMSYSERR_BADDEVICEID ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
#define  MidiInDevice 131 
#define  MidiOutDevice 130 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ SOUND_MAX_DEVICES ; 
 int SOUND_MAX_DEVICE_NAME ; 
 int /*<<< orphan*/  TranslateStatus () ; 
 scalar_t__ WAVE_IN_DEVICE_NAME_U ; 
 scalar_t__ WAVE_OUT_DEVICE_NAME_U ; 
#define  WaveInDevice 129 
#define  WaveOutDevice 128 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 

MMRESULT OpenDevice(UINT DeviceType, DWORD ID, PHANDLE pDeviceHandle,
                    DWORD Access)
{
    DPRINT("OpenDevice()\n");
    WCHAR DeviceName[SOUND_MAX_DEVICE_NAME];
    *pDeviceHandle = INVALID_HANDLE_VALUE;

    if (ID > SOUND_MAX_DEVICES)
        return MMSYSERR_BADDEVICEID;

    switch(DeviceType)
    {
        case WaveOutDevice :
            wsprintf(DeviceName, L"\\\\.%ls%d", WAVE_OUT_DEVICE_NAME_U + strlen("\\Device"), ID);
            break;
        case WaveInDevice :
            wsprintf(DeviceName, L"\\\\.%ls%d", WAVE_IN_DEVICE_NAME_U + strlen("\\Device"), ID);
            break;
        case MidiOutDevice :
            wsprintf(DeviceName, L"\\\\.%ls%d", MIDI_OUT_DEVICE_NAME_U + strlen("\\Device"), ID);
            break;
        case MidiInDevice :
            wsprintf(DeviceName, L"\\\\.%ls%d", MIDI_IN_DEVICE_NAME_U + strlen("\\Device"), ID);
            break;
		case AuxDevice :
			 wsprintf(DeviceName, L"\\\\.%ls%d", AUX_DEVICE_NAME_U + strlen("\\Device"), ID);
			 break;
        default : 
            DPRINT("No Auido Device Found");
            return MMSYSERR_BADDEVICEID; /* Maybe we should change error code */
    };

    DPRINT("Attempting to open %S\n", DeviceName);

    *pDeviceHandle = CreateFile(DeviceName, Access, FILE_SHARE_WRITE, NULL,
                                OPEN_EXISTING, Access != GENERIC_READ ? FILE_FLAG_OVERLAPPED : 0,
                                NULL);

    DPRINT("DeviceHandle == 0x%x\n", (int)*pDeviceHandle);

    if (pDeviceHandle == INVALID_HANDLE_VALUE)
        return TranslateStatus();

    return MMSYSERR_NOERROR;
}