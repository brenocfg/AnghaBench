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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int /*<<< orphan*/ * PBOOL ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DhcpCApiCleanup () ; 
 scalar_t__ DhcpCApiInitialize (scalar_t__*) ; 
 scalar_t__ DhcpRosGetAdapterInfo (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INADDR_NONE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

DWORD getDhcpInfoForAdapter(DWORD AdapterIndex,
                            PBOOL DhcpEnabled,
                            PDWORD DhcpServer,
                            time_t *LeaseObtained,
                            time_t *LeaseExpires)
{
    DWORD Status, Version = 0;

    Status = DhcpCApiInitialize(&Version);
    if (Status != ERROR_SUCCESS)
    {
        /* We assume that the DHCP service isn't running yet */
        *DhcpEnabled = FALSE;
        *DhcpServer = htonl(INADDR_NONE);
        *LeaseObtained = 0;
        *LeaseExpires = 0;
        return ERROR_SUCCESS;
    }

    Status = DhcpRosGetAdapterInfo(AdapterIndex, DhcpEnabled, DhcpServer,
                                   LeaseObtained, LeaseExpires);

    DhcpCApiCleanup();

    return Status;
}