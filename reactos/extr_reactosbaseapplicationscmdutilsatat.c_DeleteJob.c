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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Confirm () ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IDS_DELETE_ALL ; 
 scalar_t__ NERR_Success ; 
 scalar_t__ NetScheduleJobDel (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PrintErrorMessage (scalar_t__) ; 
 int /*<<< orphan*/  StdOut ; 

__attribute__((used)) static
INT
DeleteJob(
    PWSTR pszComputerName,
    ULONG ulJobId,
    BOOL bForceDelete)
{
    NET_API_STATUS Status;

    if (ulJobId == (ULONG)-1 && bForceDelete == FALSE)
    {
        ConResPrintf(StdOut, IDS_DELETE_ALL);
        if (!Confirm())
            return 0;
    }

    Status = NetScheduleJobDel(pszComputerName,
                               (ulJobId == (ULONG)-1) ? 0 : ulJobId,
                               (ulJobId == (ULONG)-1) ? -1 : ulJobId);
    if (Status != NERR_Success)
    {
        PrintErrorMessage(Status);
        return 1;
    }

    return 0;
}