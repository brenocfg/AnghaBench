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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_HELP_CMD_SELECT ; 
 int /*<<< orphan*/  SelectDisk (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SelectPartition (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wcsicmp (int /*<<< orphan*/ ,char*) ; 

BOOL
select_main(
    INT argc,
    LPWSTR *argv)
{
    /* gets the first word from the string */
    if (argc == 1)
    {
        ConResPuts(StdOut, IDS_HELP_CMD_SELECT);
        return TRUE;
    }

    /* determines which to list (disk, partition, etc.) */
    if (!wcsicmp(argv[1], L"disk"))
        SelectDisk(argc, argv);
    else if (!wcsicmp(argv[1], L"partition"))
        SelectPartition(argc, argv);
    else
        ConResPuts(StdOut, IDS_HELP_CMD_SELECT);

    return TRUE;
}