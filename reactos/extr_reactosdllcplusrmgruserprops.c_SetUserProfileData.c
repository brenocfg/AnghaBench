#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  szUserName; } ;
struct TYPE_5__ {void* usri3_home_dir_drive; int /*<<< orphan*/ * usri3_home_dir; int /*<<< orphan*/ * usri3_script_path; int /*<<< orphan*/ * usri3_profile; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PUSER_INFO_3 ;
typedef  TYPE_2__* PPROFILE_USER_DATA ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  void* LPTSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ BST_CHECKED ; 
 int CB_ERR ; 
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETLBTEXT ; 
 int /*<<< orphan*/  CB_GETLBTEXTLEN ; 
 int /*<<< orphan*/  DebugPrintf (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetWindowTextLength (int /*<<< orphan*/ ) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  IDC_USER_PROFILE_DRIVE ; 
 int /*<<< orphan*/  IDC_USER_PROFILE_LOCAL ; 
 int /*<<< orphan*/  IDC_USER_PROFILE_LOCAL_PATH ; 
 int /*<<< orphan*/  IDC_USER_PROFILE_PATH ; 
 int /*<<< orphan*/  IDC_USER_PROFILE_REMOTE_PATH ; 
 int /*<<< orphan*/  IDC_USER_PROFILE_SCRIPT ; 
 scalar_t__ IsDlgButtonChecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NERR_Success ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_1__*) ; 
 int /*<<< orphan*/  NetUserGetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ NetUserSetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char*) ; 

__attribute__((used)) static BOOL
SetUserProfileData(HWND hwndDlg,
                   PPROFILE_USER_DATA pUserData)
{
    PUSER_INFO_3 pUserInfo = NULL;
    LPTSTR pszProfilePath = NULL;
    LPTSTR pszScriptPath = NULL;
    LPTSTR pszHomeDir = NULL;
    LPTSTR pszHomeDrive = NULL;
    NET_API_STATUS status;
    DWORD dwIndex;
    INT nLength;
    INT nIndex;

    NetUserGetInfo(NULL, pUserData->szUserName, 3, (LPBYTE*)&pUserInfo);

    /* Get the profile path */
    nLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_USER_PROFILE_PATH));
    if (nLength == 0)
    {
        pUserInfo->usri3_profile = NULL;
    }
    else
    {
        pszProfilePath = HeapAlloc(GetProcessHeap(), 0, (nLength + 1) * sizeof(TCHAR));
        GetDlgItemText(hwndDlg, IDC_USER_PROFILE_PATH, pszProfilePath, nLength + 1);
        pUserInfo->usri3_profile = pszProfilePath;
    }

    /* Get the script path */
    nLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_USER_PROFILE_SCRIPT));
    if (nLength == 0)
    {
        pUserInfo->usri3_script_path = NULL;
    }
    else
    {
        pszScriptPath = HeapAlloc(GetProcessHeap(), 0, (nLength + 1) * sizeof(TCHAR));
        GetDlgItemText(hwndDlg, IDC_USER_PROFILE_SCRIPT, pszScriptPath, nLength + 1);
        pUserInfo->usri3_script_path = pszScriptPath;
    }

    if (IsDlgButtonChecked(hwndDlg, IDC_USER_PROFILE_LOCAL) == BST_CHECKED)
    {
        /* Local home directory */
        nLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_USER_PROFILE_LOCAL_PATH));
        if (nLength == 0)
        {
            pUserInfo->usri3_home_dir = NULL;
        }
        else
        {
            pszHomeDir = HeapAlloc(GetProcessHeap(), 0, (nLength + 1) * sizeof(TCHAR));
            GetDlgItemText(hwndDlg, IDC_USER_PROFILE_LOCAL_PATH, pszHomeDir, nLength + 1);
            pUserInfo->usri3_home_dir = pszHomeDir;
        }
    }
    else
    {
        /* Remote home directory */
        nLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_USER_PROFILE_REMOTE_PATH));
        if (nLength == 0)
        {
            pUserInfo->usri3_home_dir = NULL;
        }
        else
        {
            pszHomeDir = HeapAlloc(GetProcessHeap(), 0, (nLength + 1) * sizeof(TCHAR));
            GetDlgItemText(hwndDlg, IDC_USER_PROFILE_REMOTE_PATH, pszHomeDir, nLength + 1);
            pUserInfo->usri3_home_dir = pszHomeDir;
        }

        nIndex = SendMessage(GetDlgItem(hwndDlg, IDC_USER_PROFILE_DRIVE), CB_GETCURSEL, 0, 0);
        if (nIndex != CB_ERR)
        {
            nLength = SendMessage(GetDlgItem(hwndDlg, IDC_USER_PROFILE_DRIVE), CB_GETLBTEXTLEN, nIndex, 0);
            pszHomeDrive = HeapAlloc(GetProcessHeap(), 0, (nLength + 1) * sizeof(TCHAR));
            SendMessage(GetDlgItem(hwndDlg, IDC_USER_PROFILE_DRIVE), CB_GETLBTEXT, nIndex, (LPARAM)pszHomeDrive);
            pUserInfo->usri3_home_dir_drive = pszHomeDrive;
        }
    }

    status = NetUserSetInfo(NULL, pUserData->szUserName, 3, (LPBYTE)pUserInfo, &dwIndex);
    if (status != NERR_Success)
    {
        DebugPrintf(_T("Status: %lu  Index: %lu"), status, dwIndex);
    }

    if (pszProfilePath)
        HeapFree(GetProcessHeap(), 0, pszProfilePath);

    if (pszScriptPath)
        HeapFree(GetProcessHeap(), 0, pszScriptPath);

    if (pszHomeDir)
        HeapFree(GetProcessHeap(), 0, pszHomeDir);

    if (pszHomeDrive)
        HeapFree(GetProcessHeap(), 0, pszHomeDrive);

    NetApiBufferFree(pUserInfo);

    return (status == NERR_Success);
}