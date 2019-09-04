#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ dwCallback; } ;
struct TYPE_5__ {scalar_t__ dwReturn; int /*<<< orphan*/  dwItem; scalar_t__ dwCallback; } ;
struct TYPE_4__ {scalar_t__ wDeviceID; int /*<<< orphan*/ * lpstrAlias; int /*<<< orphan*/ * lpstrElementName; int /*<<< orphan*/  lpstrDeviceType; scalar_t__ dwCallback; } ;
typedef  TYPE_1__ MCI_OPEN_PARMS ;
typedef  TYPE_2__ MCI_GETDEVCAPS_PARMS ;
typedef  TYPE_3__ MCI_GENERIC_PARMS ;
typedef  scalar_t__ MCIERROR ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MCI_CLOSE ; 
 int /*<<< orphan*/  MCI_GETDEVCAPS ; 
 int MCI_GETDEVCAPS_ITEM ; 
 int /*<<< orphan*/  MCI_GETDEVCAPS_USES_FILES ; 
 int /*<<< orphan*/  MCI_OPEN ; 
 int MCI_OPEN_TYPE ; 
 int MCI_WAIT ; 
 scalar_t__ mciSendCommand (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
DeviceUsesFiles(LPTSTR lpDeviceName)
{
    MCIERROR mciError;
    MCI_OPEN_PARMS mciOpen;
    MCI_GETDEVCAPS_PARMS mciDevCaps;
    MCI_GENERIC_PARMS mciGeneric;

    mciOpen.dwCallback = 0;
    mciOpen.wDeviceID  = 0;
    mciOpen.lpstrDeviceType  = lpDeviceName;
    mciOpen.lpstrElementName = NULL;
    mciOpen.lpstrAlias = NULL;

    mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_WAIT, (DWORD_PTR)&mciOpen);
    if (mciError != 0)
        return FALSE;

    mciDevCaps.dwCallback  = 0;
    mciDevCaps.dwReturn = 0;
    mciDevCaps.dwItem = MCI_GETDEVCAPS_USES_FILES;

    mciError = mciSendCommand(mciOpen.wDeviceID, MCI_GETDEVCAPS, MCI_WAIT | MCI_GETDEVCAPS_ITEM, (DWORD_PTR)&mciDevCaps);
    if (mciError != 0)
        return FALSE;

    mciGeneric.dwCallback = 0;
    mciSendCommand(mciOpen.wDeviceID, MCI_CLOSE, MCI_WAIT, (DWORD_PTR)&mciGeneric);

    return (BOOL)mciDevCaps.dwReturn;
}