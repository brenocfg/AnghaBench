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
typedef  int WCHAR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int*) ; 
 int /*<<< orphan*/  ConFormatMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConInString (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,int*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetVolumeInformationW (int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsValidPathName (int*) ; 
 int* LOWORD (int /*<<< orphan*/ ) ; 
 int MAX_DRIVE_LENGTH ; 
 int MAX_LABEL_LENGTH ; 
 int MAX_PATH ; 
 scalar_t__ PromptYesNo () ; 
 int /*<<< orphan*/  STRING_ERROR_INVALID_DRIVE ; 
 int /*<<< orphan*/  STRING_ERROR_INVALID_LABEL ; 
 int /*<<< orphan*/  STRING_LABEL_HELP ; 
 int /*<<< orphan*/  STRING_LABEL_TEXT1 ; 
 int /*<<< orphan*/  STRING_LABEL_TEXT2 ; 
 int /*<<< orphan*/  STRING_LABEL_TEXT3 ; 
 int /*<<< orphan*/  STRING_LABEL_TEXT4 ; 
 int /*<<< orphan*/  SetVolumeLabelW (int*,int*) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 int UNICODE_NULL ; 
 int towupper (int) ; 
 int /*<<< orphan*/  wcscat (int*,...) ; 
 scalar_t__ wcscmp (int*,char*) ; 
 int /*<<< orphan*/  wcscpy (int*,int*) ; 
 scalar_t__ wcslen (int*) ; 

int wmain(int argc, WCHAR *argv[])
{
    WCHAR szRootPath[] = L" :\\";
    WCHAR szBuffer[80];
    WCHAR szLabel[80];
    WCHAR szOldLabel[80];
    DWORD dwSerialNr;
    INT len, i;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    /* set empty label string */
    szLabel[0] = UNICODE_NULL;

    /* print help */
    if (argc > 1 && wcscmp(argv[1], L"/?") == 0)
    {
        ConResPuts(StdOut, STRING_LABEL_HELP);
        return 0;
    }

    if (argc > 1)
    {
        len = 0;
        for (i = 1; i < argc; i++)
        {
            if (i > 1)
                len++;
            len += wcslen(argv[i]);
        }

        if (len > MAX_LABEL_LENGTH + MAX_DRIVE_LENGTH)
        {
            ConResPuts(StdOut, STRING_ERROR_INVALID_LABEL);
            return 1;
        }

        for (i = 1; i < argc; i++)
        {
            if (i > 1)
                wcscat(szBuffer, L" ");
            wcscat(szBuffer, argv[i]);
        }
    }

    if (wcslen(szBuffer) > 0)
    {
        if (szBuffer[1] == L':')
        {
            szRootPath[0] = towupper(szBuffer[0]);
            wcscpy(szLabel, &szBuffer[2]);
        }
        else
        {
            wcscpy(szLabel, szBuffer);
        }
    }

    if (wcslen(szLabel) > MAX_LABEL_LENGTH)
    {
        ConResPuts(StdOut, STRING_ERROR_INVALID_LABEL);
        return 1;
    }

    if (szRootPath[0] == L' ')
    {
        /* get label of current drive */
        WCHAR szCurPath[MAX_PATH];
        GetCurrentDirectoryW(MAX_PATH, szCurPath);
        szRootPath[0] = szCurPath[0];
    }

    /* check root path */
    if (!IsValidPathName(szRootPath))
    {
        ConResPuts(StdErr, STRING_ERROR_INVALID_DRIVE);
        return 1;
    }

    if (wcslen(szLabel) == 0)
    {
        GetVolumeInformationW(szRootPath, szOldLabel, ARRAYSIZE(szOldLabel), &dwSerialNr,
                              NULL, NULL, NULL, 0);

        /* print drive info */
        if (szOldLabel[0] != UNICODE_NULL)
        {
            ConResPrintf(StdOut, STRING_LABEL_TEXT1, towupper(szRootPath[0]), szOldLabel);
        }
        else
        {
            ConResPrintf(StdOut, STRING_LABEL_TEXT2, towupper(szRootPath[0]));
        }

        /* print the volume serial number */
        ConResPrintf(StdOut, STRING_LABEL_TEXT3, HIWORD(dwSerialNr), LOWORD(dwSerialNr));

        ConResPuts(StdOut, STRING_LABEL_TEXT4);

        ConInString(szLabel, ARRAYSIZE(szLabel));
        ConPuts(StdOut, L"\n");

        if (wcslen(szLabel) == 0)
        {
            if (PromptYesNo() == FALSE)
                return 0;
        }
    }

    if (!SetVolumeLabelW(szRootPath, szLabel))
    {
        ConFormatMessage(StdOut, GetLastError());
        return 1;
    }

    return 0;
}