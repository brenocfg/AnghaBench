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
typedef  int /*<<< orphan*/  IP_ADAPTER_INDEX_MAP ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IsWlanAdapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenAdapterHandle (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
OpenWlanAdapter(HANDLE *hAdapter, IP_ADAPTER_INDEX_MAP *IpInfo)
{
    DWORD dwCurrentIndex;

    for (dwCurrentIndex = 0; ; dwCurrentIndex++)
    {
        if (!OpenAdapterHandle(dwCurrentIndex, hAdapter, IpInfo))
            break;

        if (IsWlanAdapter(*hAdapter))
            return TRUE;
        else
            CloseHandle(*hAdapter);
    }

    return FALSE;
}