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
typedef  int /*<<< orphan*/  newl ;
typedef  int WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  hListView; } ;
typedef  TYPE_1__* PMAIN_WND_INFO ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int GetTextFromListView (TYPE_1__*,int*,scalar_t__,scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ ListView_GetItemCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,int*,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
SaveServicesToFile(PMAIN_WND_INFO Info,
                   LPCWSTR pszFileName)
{
    HANDLE hFile;
    BOOL bSuccess = FALSE;

    hFile = CreateFileW(pszFileName,
                       GENERIC_WRITE,
                       0,
                       NULL,
                       CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);

    if(hFile != INVALID_HANDLE_VALUE)
    {
        WCHAR LVText[500];
        WCHAR newl[2] = {L'\r', L'\n'};
        WCHAR tab = L'\t';
        DWORD dwTextLength, dwWritten;
        INT NumListedServ = 0;
        INT i, k;

        NumListedServ = ListView_GetItemCount(Info->hListView);

        for (i=0; i < NumListedServ; i++)
        {
            for (k=0; k<5; k++)
            {
                dwTextLength = GetTextFromListView(Info,
                                                   LVText,
                                                   i,
                                                   k);
                if (dwTextLength != 0)
                {
                    WriteFile(hFile,
                              LVText,
                              sizeof(WCHAR) * dwTextLength,
                              &dwWritten,
                              NULL);

                    WriteFile(hFile,
                              &tab,
                              sizeof(WCHAR),
                              &dwWritten,
                              NULL);
                }
            }
            WriteFile(hFile,
                      newl,
                      sizeof(newl),
                      &dwWritten,
                      NULL);
        }

        CloseHandle(hFile);
        bSuccess = TRUE;
    }

    return bSuccess;
}