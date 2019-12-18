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

/* Variables and functions */
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int change_command (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  change_optW ; 
 int create_command (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  create_optW ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int delete_command (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  delete_optW ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

int wmain(int argc, WCHAR *argv[])
{
    int i, ret = 0;

    for (i = 0; i < argc; i++)
        TRACE(" %s", wine_dbgstr_w(argv[i]));
    TRACE("\n");

    CoInitialize(NULL);

    if (argc < 2)
        FIXME("Print current tasks state\n");
    else if (!strcmpiW(argv[1], change_optW))
        ret = change_command(argc - 2, argv + 2);
    else if (!strcmpiW(argv[1], create_optW))
        ret = create_command(argc - 2, argv + 2);
    else if (!strcmpiW(argv[1], delete_optW))
        ret = delete_command(argc - 2, argv + 2);
    else
        FIXME("Unsupported command %s\n", debugstr_w(argv[1]));

    CoUninitialize();
    return ret;
}