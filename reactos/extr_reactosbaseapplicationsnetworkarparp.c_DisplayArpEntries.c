#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  S_addr; } ;
struct in_addr {TYPE_1__ S_un; int /*<<< orphan*/  s_addr; } ;
typedef  scalar_t__ ULONG ;
typedef  size_t UINT ;
struct TYPE_12__ {scalar_t__ dwIndex; int /*<<< orphan*/  dwAddr; } ;
struct TYPE_11__ {scalar_t__ dwNumEntries; TYPE_6__* table; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  PTCHAR ;
typedef  TYPE_2__* PMIB_IPNETTABLE ;
typedef  TYPE_2__* PMIB_IPADDRTABLE ;
typedef  TYPE_2__ MIB_IPADDRTABLE ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  DoFormatMessage () ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GetIpAddrTable (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetIpNetTable (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  NO_ERROR ; 
 int /*<<< orphan*/  PrintEntries (TYPE_6__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  inet_ntoa (struct in_addr) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

INT DisplayArpEntries(PTCHAR pszInetAddr, PTCHAR pszIfAddr)
{
    INT iRet;
    UINT i, k;
    PMIB_IPNETTABLE pIpNetTable = NULL;
    PMIB_IPADDRTABLE pIpAddrTable = NULL;
    ULONG Size = 0;
    struct in_addr inaddr, inaddr2;
    PTCHAR pszIpAddr;
    TCHAR szIntIpAddr[20];

    /* retrieve the IP-to-physical address mapping table */

    /* get table size */
    GetIpNetTable(pIpNetTable, &Size, 0);

    /* allocate memory for ARP address table */
    pIpNetTable = (PMIB_IPNETTABLE) HeapAlloc(GetProcessHeap(), 0, Size);
    if (pIpNetTable == NULL)
        goto cleanup;

    ZeroMemory(pIpNetTable, sizeof(*pIpNetTable));

    if (GetIpNetTable(pIpNetTable, &Size, TRUE) != NO_ERROR)
    {
        _tprintf(_T("failed to allocate memory for GetIpNetTable\n"));
        DoFormatMessage();
        goto cleanup;
    }

    /* check there are entries in the table */
    if (pIpNetTable->dwNumEntries == 0)
    {
        _tprintf(_T("No ARP entires found\n"));
        goto cleanup;
    }



    /* Retrieve the interface-to-ip address mapping
     * table to get the IP address for adapter */

    /* get table size */
    Size = 0;
    GetIpAddrTable(pIpAddrTable, &Size, 0);

    pIpAddrTable = (MIB_IPADDRTABLE *) HeapAlloc(GetProcessHeap(), 0, Size);
    if (pIpAddrTable == NULL)
        goto cleanup;

    ZeroMemory(pIpAddrTable, sizeof(*pIpAddrTable));

    if ((iRet = GetIpAddrTable(pIpAddrTable, &Size, TRUE)) != NO_ERROR)
    {
        _tprintf(_T("GetIpAddrTable failed: %d\n"), iRet);
        DoFormatMessage();
        goto cleanup;
    }


    for (k=0; k < pIpAddrTable->dwNumEntries; k++)
    {
        if (pIpNetTable->table[0].dwIndex == pIpAddrTable->table[k].dwIndex)
        {
            //printf("debug print: pIpAddrTable->table[?].dwIndex = %lx\n", pIpNetTable->table[k].dwIndex);
            inaddr2.s_addr = pIpAddrTable->table[k].dwAddr;
            pszIpAddr = inet_ntoa(inaddr2);
            strcpy(szIntIpAddr, pszIpAddr);
        }
    }


    /* print header, including interface IP address and index number */
    _tprintf(_T("\nInterface: %s --- 0x%lx \n"), szIntIpAddr, pIpNetTable->table[0].dwIndex);
    _tprintf(_T("  Internet Address      Physical Address      Type\n"));

    /* go through all ARP entries */
    for (i=0; i < pIpNetTable->dwNumEntries; i++)
    {

        /* if the user has supplied their own internet address *
         * only print the arp entry which matches that */
        if (pszInetAddr)
        {
            inaddr.S_un.S_addr = pIpNetTable->table[i].dwAddr;
            pszIpAddr = inet_ntoa(inaddr);

            /* check if it matches, print it */
            if (strcmp(pszIpAddr, pszInetAddr) == 0)
                PrintEntries(&pIpNetTable->table[i]);
        }
        else
            /* if an address is not supplied, print all entries */
            PrintEntries(&pIpNetTable->table[i]);
    }

    return EXIT_SUCCESS;

cleanup:
    if (pIpNetTable != NULL)
        HeapFree(GetProcessHeap(), 0, pIpNetTable);
    if (pIpAddrTable != NULL)
        HeapFree(GetProcessHeap(), 0, pIpAddrTable);
    return EXIT_FAILURE;
}