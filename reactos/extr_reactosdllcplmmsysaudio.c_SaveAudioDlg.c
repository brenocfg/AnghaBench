#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ bMIDIOutChanged; scalar_t__ bAudioInChanged; scalar_t__ bAudioOutChanged; } ;
typedef  TYPE_1__* PGLOBAL_DATA ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  IDC_DEVICE_MIDI_LIST ; 
 int /*<<< orphan*/  IDC_DEVICE_PLAY_LIST ; 
 int /*<<< orphan*/  IDC_DEVICE_REC_LIST ; 
 int /*<<< orphan*/  UpdateRegistryString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

VOID
SaveAudioDlg(HWND hwnd, PGLOBAL_DATA pGlobalData)
{
    if (pGlobalData->bAudioOutChanged)
    {
        UpdateRegistryString(hwnd,
                             IDC_DEVICE_PLAY_LIST,
                             L"Software\\Microsoft\\Multimedia\\Sound Mapper",
                             L"Playback");
    }

    if (pGlobalData->bAudioInChanged)
    {
        UpdateRegistryString(hwnd,
                             IDC_DEVICE_REC_LIST,
                             L"Software\\Microsoft\\Multimedia\\Sound Mapper",
                             L"Record");
    }

    if (pGlobalData->bMIDIOutChanged)
    {
        UpdateRegistryString(hwnd,
                             IDC_DEVICE_MIDI_LIST,
                             L"Software\\Microsoft\\Windows\\CurrentVersion\\Multimedia\\MIDIMap",
                             L"szPname");
    }
}