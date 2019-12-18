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
typedef  int INT ;

/* Variables and functions */
 int AddSubst (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DeleteSubst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpSubstedDrives () ; 
 int /*<<< orphan*/  IDS_INCORRECT_PARAMETER_COUNT ; 
 int /*<<< orphan*/  IDS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  _wcsicmp (int /*<<< orphan*/ *,char*) ; 

int wmain(int argc, WCHAR* argv[])
{
    INT i;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    for (i = 0; i < argc; i++)
    {
        if (!_wcsicmp(argv[i], L"/?"))
        {
            ConResPuts(StdOut, IDS_USAGE);
            return 0;
        }
    }

    if (argc < 3)
    {
        if (argc >= 2)
        {
            ConResPrintf(StdErr, IDS_INVALID_PARAMETER, argv[1]);
            return 1;
        }
        DumpSubstedDrives();
        return 0;
    }

    if (argc > 3)
    {
        ConResPrintf(StdErr, IDS_INCORRECT_PARAMETER_COUNT, argv[3]);
        return 1;
    }

    if (!_wcsicmp(argv[1], L"/D"))
        return DeleteSubst(argv[2]);
    if (!_wcsicmp(argv[2], L"/D"))
        return DeleteSubst(argv[1]);
    return AddSubst(argv[1], argv[2]);
}