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
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreatePartitionList () ; 
 int /*<<< orphan*/  DestroyPartitionList () ; 
 int /*<<< orphan*/  IDS_RESCAN_END ; 
 int /*<<< orphan*/  IDS_RESCAN_START ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  TRUE ; 

BOOL rescan_main(INT argc, LPWSTR *argv)
{
    ConResPuts(StdOut, IDS_RESCAN_START);
    DestroyPartitionList();
    CreatePartitionList();
    ConResPuts(StdOut, IDS_RESCAN_END);

    return TRUE;
}