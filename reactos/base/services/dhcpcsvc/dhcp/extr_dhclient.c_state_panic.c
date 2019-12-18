#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct interface_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dwIndex; } ;
struct TYPE_5__ {int /*<<< orphan*/  NteInstance; int /*<<< orphan*/  NteContext; TYPE_1__ IfMib; } ;
typedef  TYPE_2__* PDHCP_ADAPTER ;

/* Variables and functions */
 TYPE_2__* AdapterFindInfo (struct interface_info*) ; 
 int /*<<< orphan*/  AddIPAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DbgPrint (char*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  note (char*) ; 
 int rand () ; 

void
state_panic(void *ipp)
{
	struct interface_info *ip = ipp;
        PDHCP_ADAPTER Adapter = AdapterFindInfo(ip);

	note("No DHCPOFFERS received.");

        if (!Adapter->NteContext)
        {
            /* Generate an automatic private address */
            DbgPrint("DHCPCSVC: Failed to receive a response from a DHCP server. An automatic private address will be assigned.\n");

            /* FIXME: The address generation code sucks */
            AddIPAddress(htonl(0xA9FE0000 | (rand() % 0xFFFF)), //169.254.X.X
                         htonl(0xFFFF0000), //255.255.0.0
                         Adapter->IfMib.dwIndex,
                         &Adapter->NteContext,
                         &Adapter->NteInstance);
        }
}