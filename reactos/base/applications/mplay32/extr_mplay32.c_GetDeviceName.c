#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  wDeviceType; void* dwNumber; void* dwRetSize; int /*<<< orphan*/  lpstrReturn; scalar_t__ dwCallback; } ;
typedef  TYPE_1__ MCI_SYSINFO_PARMS ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  MCI_ALL_DEVICE_ID ; 
 int /*<<< orphan*/  MCI_DEVTYPE_WAVEFORM_AUDIO ; 
 int /*<<< orphan*/  MCI_SYSINFO ; 
 int /*<<< orphan*/  MCI_SYSINFO_NAME ; 
 void* mciSendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD
GetDeviceName(DWORD dwDeviceIndex, LPTSTR lpDeviceName, DWORD dwDeviceNameSize)
{
    MCI_SYSINFO_PARMS mciSysInfo;

    mciSysInfo.dwCallback  = 0;
    mciSysInfo.lpstrReturn = lpDeviceName;
    mciSysInfo.dwRetSize   = dwDeviceNameSize;
    mciSysInfo.dwNumber    = dwDeviceIndex;
    mciSysInfo.wDeviceType = MCI_DEVTYPE_WAVEFORM_AUDIO;

    return mciSendCommand(MCI_ALL_DEVICE_ID, MCI_SYSINFO, MCI_SYSINFO_NAME, (DWORD_PTR)&mciSysInfo);
}