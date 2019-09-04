#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  S_addr; } ;
struct TYPE_8__ {TYPE_1__ S_un; } ;
struct TYPE_7__ {int dwType; int /*<<< orphan*/ * bPhysAddr; int /*<<< orphan*/  dwAddr; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_2__* PMIB_IPNETROW ;
typedef  TYPE_3__ IN_ADDR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
#define  MIB_IPNET_TYPE_DYNAMIC 131 
#define  MIB_IPNET_TYPE_INVALID 130 
#define  MIB_IPNET_TYPE_OTHER 129 
#define  MIB_IPNET_TYPE_STATIC 128 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _stprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_3__) ; 

INT PrintEntries(PMIB_IPNETROW pIpAddRow)
{
    IN_ADDR inaddr;
    TCHAR cMacAddr[20];

    /* print IP addresses */
    inaddr.S_un.S_addr = pIpAddRow->dwAddr;
    _tprintf(_T("  %-22s"), inet_ntoa(inaddr));

    /* print MAC address */
    _stprintf(cMacAddr, _T("%02x-%02x-%02x-%02x-%02x-%02x"),
        pIpAddRow->bPhysAddr[0],
        pIpAddRow->bPhysAddr[1],
        pIpAddRow->bPhysAddr[2],
        pIpAddRow->bPhysAddr[3],
        pIpAddRow->bPhysAddr[4],
        pIpAddRow->bPhysAddr[5]);
    _tprintf(_T("%-22s"), cMacAddr);

    /* print cache type */
    switch (pIpAddRow->dwType)
    {
        case MIB_IPNET_TYPE_DYNAMIC : _tprintf(_T("dynamic\n"));
                                      break;
        case MIB_IPNET_TYPE_STATIC : _tprintf(_T("static\n"));
                                      break;
        case MIB_IPNET_TYPE_INVALID : _tprintf(_T("invalid\n"));
                                      break;
        case MIB_IPNET_TYPE_OTHER : _tprintf(_T("other\n"));
                                      break;
    }
    return EXIT_SUCCESS;
}