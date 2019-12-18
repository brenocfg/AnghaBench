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
struct TYPE_4__ {scalar_t__ Data; int /*<<< orphan*/  Oid; } ;
typedef  int /*<<< orphan*/  QueryOid ;
typedef  scalar_t__* PULONG ;
typedef  TYPE_1__ NDISUIO_QUERY_OID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IOCTL_NDISUIO_QUERY_OID_VALUE ; 
 scalar_t__ NdisPhysicalMediumWirelessLan ; 
 int /*<<< orphan*/  OID_GEN_PHYSICAL_MEDIUM ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
IsWlanAdapter(HANDLE hAdapter)
{
    BOOL bSuccess;
    DWORD dwBytesReturned;
    NDISUIO_QUERY_OID QueryOid;

    /* WLAN drivers must support this OID */
    QueryOid.Oid = OID_GEN_PHYSICAL_MEDIUM;

    bSuccess = DeviceIoControl(hAdapter,
                               IOCTL_NDISUIO_QUERY_OID_VALUE,
                               &QueryOid,
                               sizeof(QueryOid),
                               &QueryOid,
                               sizeof(QueryOid),
                               &dwBytesReturned,
                               NULL);
    if (!bSuccess || *(PULONG)QueryOid.Data != NdisPhysicalMediumWirelessLan)
        return FALSE;

    return TRUE;
}