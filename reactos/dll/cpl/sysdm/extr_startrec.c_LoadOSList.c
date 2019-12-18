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
struct TYPE_3__ {int iFreeLdrIni; int /*<<< orphan*/  szFreeldrIni; } ;
typedef  TYPE_1__* PSTARTINFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HINF ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetSystemDrive (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INF_STYLE_OLDNT ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LoadBootSettings (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadFreeldrSettings (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PathFileExistsW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupCloseInfFile (scalar_t__) ; 
 scalar_t__ SetupOpenInfFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
LoadOSList(HWND hwndDlg, PSTARTINFO pStartInfo)
{
    DWORD dwBufSize;
    WCHAR *szSystemDrive;
    HINF hInf;

    dwBufSize = GetSystemDrive(&szSystemDrive);
    if (dwBufSize == 0)
        return FALSE;

    wcscpy(pStartInfo->szFreeldrIni, szSystemDrive);
    wcscat(pStartInfo->szFreeldrIni, L"\\freeldr.ini");

    if (PathFileExistsW(pStartInfo->szFreeldrIni))
    {
        /* Free resource previously allocated by GetSystemDrive() */
        HeapFree(GetProcessHeap(), 0, szSystemDrive);
        /* freeldr.ini exists */
        hInf = SetupOpenInfFileW(pStartInfo->szFreeldrIni,
                                NULL,
                                INF_STYLE_OLDNT,
                                NULL);

        if (hInf != INVALID_HANDLE_VALUE)
        {
            LoadFreeldrSettings(hInf, hwndDlg);
            SetupCloseInfFile(hInf);
            pStartInfo->iFreeLdrIni = 1;
            return TRUE;
        }
        return FALSE;
    }

    /* Try loading boot.ini settings */
    wcscpy(pStartInfo->szFreeldrIni, szSystemDrive);
    wcscat(pStartInfo->szFreeldrIni, L"\\boot.ini");

    /* Free resource previously allocated by GetSystemDrive() */
    HeapFree(GetProcessHeap(), 0, szSystemDrive);

    if (PathFileExistsW(pStartInfo->szFreeldrIni))
    {
        /* Load boot.ini settings */
        hInf = SetupOpenInfFileW(pStartInfo->szFreeldrIni,
                                NULL,
                                INF_STYLE_OLDNT,
                                NULL);

        if (hInf != INVALID_HANDLE_VALUE)
        {
            LoadBootSettings(hInf, hwndDlg);
            SetupCloseInfFile(hInf);
            pStartInfo->iFreeLdrIni = 2;
            return TRUE;
        }

        return FALSE;
    }

    return FALSE;
}