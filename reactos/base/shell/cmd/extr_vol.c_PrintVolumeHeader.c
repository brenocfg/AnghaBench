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
typedef  char TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConOutResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ErrorMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetVolumeInformation (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 char* LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_VOL_HELP1 ; 
 int /*<<< orphan*/  STRING_VOL_HELP2 ; 
 int /*<<< orphan*/  STRING_VOL_HELP3 ; 
 int /*<<< orphan*/  _T (char*) ; 

__attribute__((used)) static INT
PrintVolumeHeader (LPTSTR pszRootPath)
{
    TCHAR szVolName[80];
    DWORD dwSerialNr;

    /* get the volume information of the drive */
    if (!GetVolumeInformation(pszRootPath,
                             szVolName,
                             80,
                             &dwSerialNr,
                             NULL,
                             NULL,
                             NULL,
                             0))
    {
        ErrorMessage(GetLastError (), _T(""));
        return 1;
    }

    /* print drive info */
    if (szVolName[0] != '\0')
    {
        ConOutResPrintf(STRING_VOL_HELP1, pszRootPath[0],szVolName);
    }
    else
    {
        ConOutResPrintf(STRING_VOL_HELP2, pszRootPath[0]);
    }

    /* print the volume serial number */
    ConOutResPrintf(STRING_VOL_HELP3, HIWORD(dwSerialNr), LOWORD(dwSerialNr));
    return 0;
}