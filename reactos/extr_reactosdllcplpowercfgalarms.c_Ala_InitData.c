#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szMessage ;
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_8__ {TYPE_2__* DischargePolicy; } ;
struct TYPE_9__ {TYPE_3__ user; } ;
struct TYPE_6__ {int /*<<< orphan*/  EventCode; scalar_t__ Action; } ;
struct TYPE_7__ {TYPE_1__ PowerPolicy; int /*<<< orphan*/ * BatteryLevel; scalar_t__ Enable; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BST_CHECKED ; 
 int /*<<< orphan*/  BST_UNCHECKED ; 
 int /*<<< orphan*/  CheckDlgButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t DISCHARGE_POLICY_CRITICAL ; 
 size_t DISCHARGE_POLICY_LOW ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IDC_ALARM1 ; 
 int /*<<< orphan*/  IDC_ALARM2 ; 
 int /*<<< orphan*/  IDC_ALARMAKTION1 ; 
 int /*<<< orphan*/  IDC_ALARMAKTION2 ; 
 int /*<<< orphan*/  IDC_ALARMBAR1 ; 
 int /*<<< orphan*/  IDC_ALARMBAR2 ; 
 int /*<<< orphan*/  IDC_ALARMMSG1 ; 
 int /*<<< orphan*/  IDC_ALARMMSG2 ; 
 int /*<<< orphan*/  IDC_ALARMPROG1 ; 
 int /*<<< orphan*/  IDC_ALARMPROG2 ; 
 int /*<<< orphan*/  IDC_ALARMVALUE1 ; 
 int /*<<< orphan*/  IDC_ALARMVALUE2 ; 
 scalar_t__ IDS_NOACTION ; 
 scalar_t__ IDS_PERCENT ; 
 scalar_t__ IDS_PowerActionNone1 ; 
 scalar_t__ IDS_PowerActionNone2 ; 
 scalar_t__ IDS_SOUND ; 
 scalar_t__ IDS_TEXT ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ LoadString (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ MAKELONG (int /*<<< orphan*/ ,int) ; 
 int MAX_PATH ; 
 int POWER_LEVEL_USER_NOTIFY_SOUND ; 
 int POWER_LEVEL_USER_NOTIFY_TEXT ; 
 int /*<<< orphan*/  ReadGlobalPwrPolicy (TYPE_4__*) ; 
 int /*<<< orphan*/  SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TBM_SETPOS ; 
 int /*<<< orphan*/  TBM_SETRANGE ; 
 int /*<<< orphan*/  TBM_SETTICFREQ ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * _T (char*) ; 
 int /*<<< orphan*/  _stprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 TYPE_4__ gGPP ; 
 int /*<<< orphan*/  hApplet ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static BOOLEAN
Ala_InitData(HWND hwndDlg)
{
    TCHAR szAction[MAX_PATH];
    TCHAR szText[MAX_PATH];
    TCHAR szSound[MAX_PATH];
    TCHAR szMessage[MAX_PATH];
    TCHAR szTemp[MAX_PATH];
    TCHAR szBatteryLevel[MAX_PATH];
    TCHAR szProgram[MAX_PATH];

    if (!ReadGlobalPwrPolicy(&gGPP))
    {
        return FALSE;
    }

    if (gGPP.user.DischargePolicy[DISCHARGE_POLICY_LOW].Enable)
    {
        CheckDlgButton(hwndDlg, IDC_ALARM1,
            gGPP.user.DischargePolicy[DISCHARGE_POLICY_LOW].Enable ? BST_CHECKED : BST_UNCHECKED);

        if (LoadString(hApplet, IDS_PERCENT, szTemp, MAX_PATH))
        {
            _stprintf(szBatteryLevel, szTemp, gGPP.user.DischargePolicy[DISCHARGE_POLICY_LOW].BatteryLevel);
            SetDlgItemText(hwndDlg, IDC_ALARMVALUE1, szBatteryLevel);
        }

        SendDlgItemMessage(hwndDlg, IDC_ALARMBAR1,
            TBM_SETRANGE,
            (WPARAM)TRUE,
            (LPARAM)MAKELONG(0, 100));
        SendDlgItemMessage(hwndDlg, IDC_ALARMBAR1,
            TBM_SETTICFREQ,
            (WPARAM)TRUE,
            (LPARAM)20);
        SendDlgItemMessage(hwndDlg, IDC_ALARMBAR1,
            TBM_SETPOS,
            (WPARAM)TRUE,
            (LPARAM)gGPP.user.DischargePolicy[DISCHARGE_POLICY_LOW].BatteryLevel);

        if (LoadString(hApplet, gGPP.user.DischargePolicy[DISCHARGE_POLICY_LOW].PowerPolicy.Action+IDS_PowerActionNone1, szAction, MAX_PATH))
        {
            SetDlgItemText(hwndDlg, IDC_ALARMAKTION1, szAction);
        }

        memset(szMessage, 0x0, sizeof(szMessage));
        LoadString(hApplet, IDS_NOACTION, szMessage, MAX_PATH);

        if (LOWORD(gGPP.user.DischargePolicy[DISCHARGE_POLICY_LOW].PowerPolicy.EventCode) & POWER_LEVEL_USER_NOTIFY_TEXT)
        {
            if (LOWORD(gGPP.user.DischargePolicy[DISCHARGE_POLICY_LOW].PowerPolicy.EventCode) & POWER_LEVEL_USER_NOTIFY_SOUND)
            {
                if (LoadString(hApplet, IDS_SOUND, szSound, MAX_PATH) && LoadString(hApplet, IDS_TEXT, szText, MAX_PATH))
                {
                    _stprintf(szMessage,_T("%s, %s"),szSound,szText);
                }
            }
            else
            {
                if (LoadString(hApplet, IDS_TEXT, szText, MAX_PATH))
                {
                    _stprintf(szMessage,_T("%s"),szText);
                }
            }
        }
        else
        {
            if (LOWORD(gGPP.user.DischargePolicy[DISCHARGE_POLICY_LOW].PowerPolicy.EventCode) & POWER_LEVEL_USER_NOTIFY_SOUND)
            {
                if (LoadString(hApplet, IDS_SOUND, szSound, MAX_PATH))
                {
                    _stprintf(szMessage,_T("%s"),szSound);
                }
            }
        }

        SetDlgItemText(hwndDlg, IDC_ALARMMSG1, szMessage);

        if (LoadString(hApplet, IDS_PowerActionNone2, szProgram, MAX_PATH))
        {
            SetDlgItemText(hwndDlg, IDC_ALARMPROG1, szProgram);
        }
    }

    if (gGPP.user.DischargePolicy[DISCHARGE_POLICY_CRITICAL].Enable)
    {
        CheckDlgButton(hwndDlg, IDC_ALARM2,
            gGPP.user.DischargePolicy[DISCHARGE_POLICY_CRITICAL].Enable ? BST_CHECKED : BST_UNCHECKED);

        if (LoadString(hApplet, IDS_PERCENT, szTemp, MAX_PATH))
        {
            _stprintf(szBatteryLevel, szTemp, gGPP.user.DischargePolicy[DISCHARGE_POLICY_CRITICAL].BatteryLevel);
            SetDlgItemText(hwndDlg, IDC_ALARMVALUE2, szBatteryLevel);
        }

        SendDlgItemMessage(hwndDlg, IDC_ALARMBAR2,
            TBM_SETRANGE,
            (WPARAM)TRUE,
            (LPARAM)MAKELONG(0, 100));
        SendDlgItemMessage(hwndDlg, IDC_ALARMBAR2,
            TBM_SETPOS,
            (WPARAM)TRUE,
            (LPARAM)gGPP.user.DischargePolicy[DISCHARGE_POLICY_CRITICAL].BatteryLevel);

        if (LoadString(hApplet, gGPP.user.DischargePolicy[DISCHARGE_POLICY_CRITICAL].PowerPolicy.Action+IDS_PowerActionNone1, szAction, MAX_PATH))
        {
            SetDlgItemText(hwndDlg, IDC_ALARMAKTION2, szAction);
        }

        memset(szMessage, 0x0, sizeof(szMessage));
        LoadString(hApplet, IDS_NOACTION, szMessage, MAX_PATH);

        if (LOWORD(gGPP.user.DischargePolicy[DISCHARGE_POLICY_CRITICAL].PowerPolicy.EventCode) & POWER_LEVEL_USER_NOTIFY_TEXT)
        {
            if (LOWORD(gGPP.user.DischargePolicy[DISCHARGE_POLICY_CRITICAL].PowerPolicy.EventCode) & POWER_LEVEL_USER_NOTIFY_SOUND)
            {
                if (LoadString(hApplet, IDS_TEXT, szText, MAX_PATH) && LoadString(hApplet, IDS_SOUND, szSound, MAX_PATH))
                {
                    _stprintf(szMessage,_T("%s, %s"),szSound,szText);
                }
            }
            else
            {
                if (LoadString(hApplet, IDS_TEXT, szText, MAX_PATH))
                {
                    _stprintf(szMessage,_T("%s"),szText);
                }
            }
        }
        else
        {
            if (LOWORD(gGPP.user.DischargePolicy[DISCHARGE_POLICY_CRITICAL].PowerPolicy.EventCode) & POWER_LEVEL_USER_NOTIFY_SOUND)
            {
                if (LoadString(hApplet, IDS_SOUND, szSound, MAX_PATH))
                {
                    _stprintf(szMessage,_T("%s"),szSound);
                }
            }
        }

        SetDlgItemText(hwndDlg, IDC_ALARMMSG2, szMessage);

        if (LoadString(hApplet, IDS_PowerActionNone2, szProgram, MAX_PATH))
        {
            SetDlgItemText(hwndDlg, IDC_ALARMPROG2, szProgram);
        }
    }

    return TRUE;
}