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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {char* pszFullName; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  TYPE_1__* PPROFILEDATA ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BST_CHECKED ; 
 int /*<<< orphan*/  Button_SetCheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_USERPROFILE_TYPE_LOCAL ; 
 int /*<<< orphan*/  IDC_USERPROFILE_TYPE_ROAMING ; 
 int /*<<< orphan*/  IDC_USERPROFILE_TYPE_TEXT ; 
 int /*<<< orphan*/  IDOK ; 
 int /*<<< orphan*/  IDS_USERPROFILE_TYPE_TEXT ; 
 int LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hApplet ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int wcslen (char*) ; 

__attribute__((used)) static
BOOL
OnProfileTypeInit(
    HWND hwndDlg,
    PPROFILEDATA pProfileData)
{
    PWSTR pszRawBuffer = NULL, pszCookedBuffer = NULL;
    INT nLength;

    nLength = LoadStringW(hApplet, IDS_USERPROFILE_TYPE_TEXT, (PWSTR)&pszRawBuffer, 0);
    pszRawBuffer = NULL;
    if (nLength == 0)
        return FALSE;

    pszRawBuffer = HeapAlloc(GetProcessHeap(), 0, (nLength + 1) * sizeof(WCHAR));
    if (pszRawBuffer == NULL)
        return FALSE;

    LoadStringW(hApplet, IDS_USERPROFILE_TYPE_TEXT, pszRawBuffer, nLength + 1);

    pszCookedBuffer = HeapAlloc(GetProcessHeap(), 0, (nLength + wcslen(pProfileData->pszFullName) + 1) * sizeof(WCHAR));
    if (pszCookedBuffer == NULL)
        goto done;

    swprintf(pszCookedBuffer, pszRawBuffer, pProfileData->pszFullName);

    /* Set the full text */
    SetDlgItemText(hwndDlg, IDC_USERPROFILE_TYPE_TEXT, pszCookedBuffer);

    /* FIXME: Right now, we support local user profiles only! */
    EnableWindow(GetDlgItem(hwndDlg, IDC_USERPROFILE_TYPE_ROAMING), FALSE);
    Button_SetCheck(GetDlgItem(hwndDlg, IDC_USERPROFILE_TYPE_LOCAL), BST_CHECKED);
    EnableWindow(GetDlgItem(hwndDlg, IDOK), FALSE);

done:
    if (pszCookedBuffer != NULL)
        HeapFree(GetProcessHeap(), 0, pszCookedBuffer);

    if (pszRawBuffer != NULL)
        HeapFree(GetProcessHeap(), 0, pszRawBuffer);

    return TRUE;
}