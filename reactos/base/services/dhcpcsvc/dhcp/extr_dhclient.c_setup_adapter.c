#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct iaddr {scalar_t__ iabuf; } ;
struct TYPE_13__ {scalar_t__ iabuf; } ;
struct client_lease {TYPE_3__* options; TYPE_6__ address; } ;
typedef  scalar_t__ ULONG ;
struct TYPE_14__ {int dwForwardMetric1; scalar_t__ dwForwardNextHop; int /*<<< orphan*/  dwForwardIfIndex; scalar_t__ dwForwardMask; scalar_t__ dwForwardDest; } ;
struct TYPE_10__ {int /*<<< orphan*/  dwIndex; } ;
struct TYPE_9__ {char* name; } ;
struct TYPE_12__ {TYPE_7__ RouterMib; TYPE_2__ IfMib; int /*<<< orphan*/  NteInstance; int /*<<< orphan*/  NteContext; TYPE_1__ DhclientInfo; } ;
struct TYPE_11__ {int len; int* data; } ;
typedef  TYPE_4__* PDHCP_ADAPTER ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddIPAddress (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateIpForwardEntry (TYPE_7__*) ; 
 size_t DHO_ROUTERS ; 
 size_t DHO_SUBNET_MASK ; 
 int /*<<< orphan*/  DeleteIPAddress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteIpForwardEntry (TYPE_7__*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RegSetValueExA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int*,int) ; 
 char* piaddr (TYPE_6__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

void setup_adapter( PDHCP_ADAPTER Adapter, struct client_lease *new_lease ) {
    CHAR Buffer[200] = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\";
    struct iaddr netmask;
    HKEY hkey;
    int i;
    DWORD dwEnableDHCP;

    strcat(Buffer, Adapter->DhclientInfo.name);
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, Buffer, 0, KEY_WRITE, &hkey) != ERROR_SUCCESS)
        hkey = NULL;


    if( Adapter->NteContext )
    {
        DeleteIPAddress( Adapter->NteContext );
        Adapter->NteContext = 0;
    }

    /* Set up our default router if we got one from the DHCP server */
    if( new_lease->options[DHO_SUBNET_MASK].len ) {
        NTSTATUS Status;

        memcpy( netmask.iabuf,
                new_lease->options[DHO_SUBNET_MASK].data,
                new_lease->options[DHO_SUBNET_MASK].len );
        Status = AddIPAddress
            ( *((ULONG*)new_lease->address.iabuf),
              *((ULONG*)netmask.iabuf),
              Adapter->IfMib.dwIndex,
              &Adapter->NteContext,
              &Adapter->NteInstance );
        if (hkey) {
            RegSetValueExA(hkey, "DhcpIPAddress", 0, REG_SZ, (LPBYTE)piaddr(new_lease->address), strlen(piaddr(new_lease->address))+1);
            Buffer[0] = '\0';
            for(i = 0; i < new_lease->options[DHO_SUBNET_MASK].len; i++)
            {
                sprintf(&Buffer[strlen(Buffer)], "%u", new_lease->options[DHO_SUBNET_MASK].data[i]);
                if (i + 1 < new_lease->options[DHO_SUBNET_MASK].len)
                    strcat(Buffer, ".");
            }
            RegSetValueExA(hkey, "DhcpSubnetMask", 0, REG_SZ, (LPBYTE)Buffer, strlen(Buffer)+1);
            dwEnableDHCP = 1;
            RegSetValueExA(hkey, "EnableDHCP", 0, REG_DWORD, (LPBYTE)&dwEnableDHCP, sizeof(DWORD));
        }

        if( !NT_SUCCESS(Status) )
            warning("AddIPAddress: %lx\n", Status);
    }

    if( new_lease->options[DHO_ROUTERS].len ) {
        NTSTATUS Status;

        Adapter->RouterMib.dwForwardDest = 0; /* Default route */
        Adapter->RouterMib.dwForwardMask = 0;
        Adapter->RouterMib.dwForwardMetric1 = 1;
        Adapter->RouterMib.dwForwardIfIndex = Adapter->IfMib.dwIndex;

        if( Adapter->RouterMib.dwForwardNextHop ) {
            /* If we set a default route before, delete it before continuing */
            DeleteIpForwardEntry( &Adapter->RouterMib );
        }

        Adapter->RouterMib.dwForwardNextHop =
            *((ULONG*)new_lease->options[DHO_ROUTERS].data);

        Status = CreateIpForwardEntry( &Adapter->RouterMib );

        if( !NT_SUCCESS(Status) )
            warning("CreateIpForwardEntry: %lx\n", Status);

        if (hkey) {
            Buffer[0] = '\0';
            for(i = 0; i < new_lease->options[DHO_ROUTERS].len; i++)
            {
                sprintf(&Buffer[strlen(Buffer)], "%u", new_lease->options[DHO_ROUTERS].data[i]);
                if (i + 1 < new_lease->options[DHO_ROUTERS].len)
                    strcat(Buffer, ".");
            }
            RegSetValueExA(hkey, "DhcpDefaultGateway", 0, REG_SZ, (LPBYTE)Buffer, strlen(Buffer)+1);
        }
    }

    if (hkey)
        RegCloseKey(hkey);
}