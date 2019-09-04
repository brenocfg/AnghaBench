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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetConsoleCP () ; 
 int /*<<< orphan*/ * GetConsoleOutputCP () ; 
 int /*<<< orphan*/  STRING_CHCP_ERROR1 ; 
 int /*<<< orphan*/  STRING_CHCP_ERROR4 ; 
 int /*<<< orphan*/  STRING_CHCP_HELP ; 
 int /*<<< orphan*/  STRING_ERROR_INVALID_PARAM_FORMAT ; 
 scalar_t__ SetConsoleCP (scalar_t__) ; 
 scalar_t__ SetConsoleOutputCP (scalar_t__) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ _wtoi (int /*<<< orphan*/ *) ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ *,char*) ; 

int wmain(int argc, WCHAR* argv[])
{
    UINT uOldCodePage, uNewCodePage;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    /* Print help */
    if (argc > 1 && wcscmp(argv[1], L"/?") == 0)
    {
        ConResPuts(StdOut, STRING_CHCP_HELP);
        return 0;
    }

    if (argc == 1)
    {
        /* Display the active code page number */
        ConResPrintf(StdOut, STRING_CHCP_ERROR1, GetConsoleOutputCP());
        return 0;
    }

    if (argc > 2)
    {
        /* Too many parameters */
        ConResPrintf(StdErr, STRING_ERROR_INVALID_PARAM_FORMAT, argv[2]);
        return 1;
    }

    uNewCodePage = (UINT)_wtoi(argv[1]);

    if (uNewCodePage == 0)
    {
        ConResPrintf(StdErr, STRING_ERROR_INVALID_PARAM_FORMAT, argv[1]);
        return 1;
    }

    /*
     * Save the original console codepage to be restored in case
     * SetConsoleCP() or SetConsoleOutputCP() fails.
     */
    uOldCodePage = GetConsoleCP();

    /*
     * Try changing the console input codepage. If it works then also change
     * the console output codepage, and refresh our local codepage cache.
     */
    if (SetConsoleCP(uNewCodePage))
    {
        if (SetConsoleOutputCP(uNewCodePage))
        {
            /* Display the active code page number */
            ConResPrintf(StdOut, STRING_CHCP_ERROR1, GetConsoleOutputCP());
            return 0;
        }
        else
        {
            /* Failure, restore the original console codepage */
            SetConsoleCP(uOldCodePage);
        }
    }

    /* An error happened, display an error and bail out */
    ConResPuts(StdErr, STRING_CHCP_ERROR4);
    return 1;
}