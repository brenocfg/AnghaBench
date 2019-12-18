#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {int dwFileAttributes; int* cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;
typedef  int WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 scalar_t__ CB_ERR ; 
 int /*<<< orphan*/  CB_SETITEMDATA ; 
 int /*<<< orphan*/  ComboBox_AddString (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileW (int*,TYPE_1__*) ; 
 scalar_t__ FindNextFileW (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetWindowsDirectoryW (int*,int) ; 
 int /*<<< orphan*/  IDC_SOUND_LIST ; 
 int /*<<< orphan*/  IDS_NO_SOUND ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char) ; 
 int /*<<< orphan*/  TRUE ; 
 int _countof (int /*<<< orphan*/ *) ; 
 scalar_t__ _wcsdup (int*) ; 
 int /*<<< orphan*/  hApplet ; 
 int /*<<< orphan*/  wcscpy (int*,char*) ; 
 int* wcsrchr (int*,int) ; 

BOOL
LoadSoundFiles(HWND hwndDlg)
{
    TCHAR szList[256];
    WCHAR szPath[MAX_PATH];
    WCHAR * ptr;
    WIN32_FIND_DATAW FileData;
    HANDLE hFile;
    LRESULT lResult;
    UINT length;

    /* Add no sound listview item */
    if (LoadString(hApplet, IDS_NO_SOUND, szList, _countof(szList)))
    {
        szList[_countof(szList) - 1] = TEXT('\0');
        ComboBox_AddString(GetDlgItem(hwndDlg, IDC_SOUND_LIST), szList);
    }

    /* Load sound files */
    length = GetWindowsDirectoryW(szPath, MAX_PATH);
    if (length == 0 || length >= MAX_PATH - 9)
    {
        return FALSE;
    }
    if (szPath[length-1] != L'\\')
    {
        szPath[length] = L'\\';
        length++;
    }
    wcscpy(&szPath[length], L"media\\*");
    length += 7;

    hFile = FindFirstFileW(szPath, &FileData);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    do
    {
        if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;

        ptr = wcsrchr(FileData.cFileName, L'\\');
        if (ptr)
        {
            ptr++;
        }
        else
        {
            ptr = FileData.cFileName;
        }
        lResult = SendDlgItemMessageW(hwndDlg, IDC_SOUND_LIST, CB_ADDSTRING, (WPARAM)0, (LPARAM)ptr);
        if (lResult != CB_ERR)
        {
            wcscpy(&szPath[length-1], FileData.cFileName);
            SendDlgItemMessageW(hwndDlg, IDC_SOUND_LIST, CB_SETITEMDATA, (WPARAM)lResult, (LPARAM)_wcsdup(szPath));
        }
    } while (FindNextFileW(hFile, &FileData) != 0);

    FindClose(hFile);
    return TRUE;
}