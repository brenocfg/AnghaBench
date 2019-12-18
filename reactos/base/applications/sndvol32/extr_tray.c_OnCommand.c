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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {int cbStruct; int cChannels; int cbDetails; TYPE_2__* paDetails; scalar_t__ cMultipleItems; int /*<<< orphan*/  dwControlID; } ;
struct TYPE_7__ {int fValue; } ;
struct TYPE_6__ {scalar_t__ hMixer; int /*<<< orphan*/  muteControlID; } ;
typedef  TYPE_1__* PDIALOG_DATA ;
typedef  TYPE_2__ MIXERCONTROLDETAILS_BOOLEAN ;
typedef  TYPE_3__ MIXERCONTROLDETAILS ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMIXEROBJ ;

/* Variables and functions */
 int /*<<< orphan*/  BM_GETCHECK ; 
 scalar_t__ BN_CLICKED ; 
 scalar_t__ BST_CHECKED ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ IDC_LINE_SWITCH ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int MIXER_OBJECTF_HMIXER ; 
 int MIXER_SETCONTROLDETAILSF_VALUE ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixerSetControlDetails (int /*<<< orphan*/ ,TYPE_3__*,int) ; 

__attribute__((used)) static
VOID
OnCommand(
    PDIALOG_DATA pDialogData,
    HWND hwndDlg,
    WPARAM wParam,
    LPARAM lParam)
{
    MIXERCONTROLDETAILS mxcd;
    MIXERCONTROLDETAILS_BOOLEAN mxcdMute;

    if ((LOWORD(wParam) == IDC_LINE_SWITCH) &&
        (HIWORD(wParam) == BN_CLICKED))
    {
        mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
        mxcd.dwControlID = pDialogData->muteControlID;
        mxcd.cChannels = 1;
        mxcd.cMultipleItems = 0;
        mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
        mxcd.paDetails = &mxcdMute;

        mxcdMute.fValue = (SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED);

        mixerSetControlDetails((HMIXEROBJ)pDialogData->hMixer,
                               &mxcd,
                               MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE);
    }
}