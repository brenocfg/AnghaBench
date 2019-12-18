#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nChannels; int nSamplesPerSec; int nAvgBytesPerSec; int nBlockAlign; int wBitsPerSample; scalar_t__ cbSize; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_7__ {int wDevID; TYPE_1__ wfxRef; } ;
typedef  TYPE_2__ WINE_MCIWAVE ;
struct TYPE_8__ {int wDeviceID; int /*<<< orphan*/  wType; int /*<<< orphan*/  wCustomCommandTable; } ;
typedef  int LRESULT ;
typedef  TYPE_3__* LPMCI_OPEN_DRIVER_PARMSW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MCI_DEVTYPE_WAVEFORM_AUDIO ; 
 int /*<<< orphan*/  MCI_NO_COMMAND_TABLE ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  mciSetDriverData (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT WAVE_drvOpen(LPCWSTR str, LPMCI_OPEN_DRIVER_PARMSW modp)
{
    WINE_MCIWAVE*	wmw;

    if (modp == NULL) return 0xFFFFFFFF;

    wmw = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WINE_MCIWAVE));

    if (!wmw)
	return 0;

    wmw->wDevID = modp->wDeviceID;
    mciSetDriverData(wmw->wDevID, (DWORD_PTR)wmw);
    modp->wCustomCommandTable = MCI_NO_COMMAND_TABLE;
    modp->wType = MCI_DEVTYPE_WAVEFORM_AUDIO;

    wmw->wfxRef.wFormatTag     	= WAVE_FORMAT_PCM;
    wmw->wfxRef.nChannels       = 1;      /* MONO */
    wmw->wfxRef.nSamplesPerSec  = 11025;
    wmw->wfxRef.nAvgBytesPerSec = 11025;
    wmw->wfxRef.nBlockAlign     = 1;
    wmw->wfxRef.wBitsPerSample  = 8;
    wmw->wfxRef.cbSize          = 0;      /* don't care */

    return modp->wDeviceID;
}