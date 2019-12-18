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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  DirectPlay8SP ; 
 int /*<<< orphan*/  DirectPlaySP ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ EnumerateServiceProviders (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  IDC_LIST_PROVIDER ; 
 int /*<<< orphan*/  InitListViewColumns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  LVM_SETEXTENDEDLISTVIEWSTYLE ; 
 int /*<<< orphan*/  LVS_EX_FULLROWSELECT ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
InitializeDirectPlayDialog(HWND hwndDlg)
{
    HKEY hKey;
    LONG result;
    HWND hDlgCtrl;

    /* open DirectPlay8 key */
    result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\DirectPlay8\\Service Providers", 0, KEY_READ, &hKey);
    if (result != ERROR_SUCCESS)
        return;

    hDlgCtrl = GetDlgItem(hwndDlg, IDC_LIST_PROVIDER);

    /* Highlights the entire row instead of just the selected item in the first column */
    SendMessage(hDlgCtrl, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

    /* initialize list ctrl */
    InitListViewColumns(hDlgCtrl);

    /* enumerate providers */
    result = EnumerateServiceProviders(hKey, hDlgCtrl, DirectPlay8SP);
    RegCloseKey(hKey);
    if (!result)
        return;

    /* open DirectPlay key */
    result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\DirectPlay\\Service Providers", 0, KEY_READ, &hKey);
    if (result != ERROR_SUCCESS)
        return;

    /* enumerate providers */
    EnumerateServiceProviders(hKey, hDlgCtrl, DirectPlaySP);
    RegCloseKey(hKey);
}