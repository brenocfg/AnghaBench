#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_10__ {int cbStruct; size_t cChannels; int cbDetails; TYPE_2__* paDetails; int /*<<< orphan*/  cMultipleItems; int /*<<< orphan*/  dwControlID; } ;
struct TYPE_9__ {size_t volumeMinimum; size_t volumeMaximum; size_t volumeStep; size_t volumeChannels; size_t maxVolume; int /*<<< orphan*/  hMixer; TYPE_2__* volumeCurrentValues; int /*<<< orphan*/  volumeControlID; TYPE_1__* volumeInitValues; } ;
struct TYPE_8__ {size_t dwValue; } ;
struct TYPE_7__ {size_t dwValue; } ;
typedef  TYPE_3__* PDIALOG_DATA ;
typedef  int /*<<< orphan*/  MIXERCONTROLDETAILS_UNSIGNED ;
typedef  TYPE_4__ MIXERCONTROLDETAILS ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMIXEROBJ ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IDC_LINE_SLIDER_VERT ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int MIXER_OBJECTF_HMIXER ; 
 int MIXER_SETCONTROLDETAILSF_VALUE ; 
 int /*<<< orphan*/  PlaySound (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int SND_ALIAS_ID ; 
 int /*<<< orphan*/  SND_ALIAS_SYSTEMDEFAULT ; 
 int SND_ASYNC ; 
 int /*<<< orphan*/  SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBM_GETPOS ; 
#define  TB_ENDTRACK 129 
#define  TB_THUMBPOSITION 128 
 size_t VOLUME_MAX ; 
 size_t VOLUME_MIN ; 
 int /*<<< orphan*/  mixerSetControlDetails (int /*<<< orphan*/ ,TYPE_4__*,int) ; 

__attribute__((used)) static
VOID
OnVScroll(
    PDIALOG_DATA pDialogData,
    HWND hwndDlg,
    WPARAM wParam,
    LPARAM lParam)
{
    MIXERCONTROLDETAILS mxcd;
    DWORD dwPosition, dwVolume, i;

    switch (LOWORD(wParam))
    {
        case TB_THUMBPOSITION:
            break;

        case TB_ENDTRACK:
            PlaySound((LPCTSTR)SND_ALIAS_SYSTEMDEFAULT, NULL, SND_ASYNC | SND_ALIAS_ID);
            break;

        default:
            dwPosition = VOLUME_MAX - (DWORD)SendDlgItemMessage(hwndDlg, IDC_LINE_SLIDER_VERT, TBM_GETPOS, 0, 0);

            if (dwPosition == VOLUME_MIN)
                dwVolume = pDialogData->volumeMinimum;
            else if (dwPosition == VOLUME_MAX)
                dwVolume = pDialogData->volumeMaximum;
            else
                dwVolume = (dwPosition * pDialogData->volumeStep) + pDialogData->volumeMinimum;

            for (i = 0; i < pDialogData->volumeChannels; i++)
            {
                if (pDialogData->volumeInitValues[i].dwValue == pDialogData->maxVolume)
                {
                    pDialogData->volumeCurrentValues[i].dwValue = dwVolume;
                }
                else
                {
                    pDialogData->volumeCurrentValues[i].dwValue =
                        pDialogData->volumeInitValues[i].dwValue * dwVolume / pDialogData-> maxVolume;
                }
            }

            mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
            mxcd.dwControlID = pDialogData->volumeControlID;
            mxcd.cChannels = pDialogData->volumeChannels;
            mxcd.cMultipleItems = 0;
            mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
            mxcd.paDetails = pDialogData->volumeCurrentValues;

            mixerSetControlDetails((HMIXEROBJ)pDialogData->hMixer,
                                   &mxcd,
                                   MIXER_OBJECTF_HMIXER | MIXER_SETCONTROLDETAILSF_VALUE);
            break;
    }
}