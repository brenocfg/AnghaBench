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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/ * GetCommandLineW () ; 
 int /*<<< orphan*/  RunInstallReactOS (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * wcschr (int /*<<< orphan*/ *,int) ; 

INT wmain(INT argc, WCHAR* argv[])
{
    LPWSTR CmdLine, p;

    // NOTE: Temporary, until we correctly use argc/argv.
    CmdLine = GetCommandLineW();
    DPRINT("CmdLine: <%S>\n", CmdLine);

    p = wcschr(CmdLine, L'-');
    if (p == NULL)
        return ERROR_INVALID_PARAMETER;
    p++;

    // NOTE: On Windows, "mini" means "minimal UI", and can be used
    // in addition to "newsetup"; these options are not exclusive.
    if (_wcsicmp(p, L"newsetup") == 0 || _wcsicmp(p, L"mini") == 0)
    {
        RunInstallReactOS(argc, argv);
    }

#if 0
    /* Add new setup types here */
    else if (...)
    {

    }
#endif

    return 0;
}