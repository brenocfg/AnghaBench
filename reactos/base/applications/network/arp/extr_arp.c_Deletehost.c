#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_10__ {int /*<<< orphan*/  dwAddr; int /*<<< orphan*/  dwIndex; TYPE_1__* table; } ;
struct TYPE_9__ {int /*<<< orphan*/  dwIndex; } ;
typedef  int /*<<< orphan*/ * PTCHAR ;
typedef  TYPE_2__* PMIB_IPNETTABLE ;
typedef  TYPE_2__* PMIB_IPNETROW ;
typedef  TYPE_2__ MIB_IPNETROW ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DeleteIpNetEntry (TYPE_2__*) ; 
 int /*<<< orphan*/  DoFormatMessage () ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ FlushIpNetTable (int /*<<< orphan*/ ) ; 
 scalar_t__ GetIpNetTable (TYPE_2__*,int*,scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  INADDR_NONE ; 
 scalar_t__ NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  Usage () ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ sscanf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 

INT Deletehost(PTCHAR pszInetAddr, PTCHAR pszIfAddr)
{
    PMIB_IPNETROW pDelHost = NULL;
    PMIB_IPNETTABLE pIpNetTable = NULL;
    ULONG Size = 0;
    DWORD dwIpAddr = 0;
    BOOL bFlushTable = FALSE;

    /* error checking */

    /* check IP address */
    if (pszInetAddr != NULL)
    {
        /* if wildcard is given, set flag to delete all hosts */
        if (strncmp(pszInetAddr, "*", 1) == 0)
            bFlushTable = TRUE;
        else if ((dwIpAddr = inet_addr(pszInetAddr)) == INADDR_NONE)
        {
            _tprintf(_T("ARP: bad IP address: %s\n"), pszInetAddr);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        Usage();
        exit(EXIT_FAILURE);
    }

    /* We need the IpNetTable to get the adapter index */
    /* Return required buffer size */
    GetIpNetTable(NULL, &Size, 0);

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

    /* reserve memory on heap and zero */
    pDelHost = (MIB_IPNETROW *) HeapAlloc(GetProcessHeap(), 0, sizeof(MIB_IPNETROW));
    if (pDelHost == NULL)
        goto cleanup;

    ZeroMemory(pDelHost, sizeof(MIB_IPNETROW));


    /* set dwIndex field to the index of a local IP address to
     * indicate the network on which the ARP entry applies */
    if (pszIfAddr)
    {
        if (sscanf(pszIfAddr, "%lx", &pDelHost->dwIndex) == EOF)
        {
            goto cleanup;
        }
    }
    else
    {
        /* needs testing. I get the correct index on my machine, but need others
         * to test their card index. Any problems and we can use GetAdaptersInfo instead */
        pDelHost->dwIndex = pIpNetTable->table[0].dwIndex;
    }

    if (bFlushTable != FALSE)
    {
        /* delete arp cache */
        if (FlushIpNetTable(pDelHost->dwIndex) != NO_ERROR)
        {
            DoFormatMessage();
            goto cleanup;
        }
        else
        {
            HeapFree(GetProcessHeap(), 0, pDelHost);
            return EXIT_SUCCESS;
        }
    }
    else
        /* copy converted IP address */
        pDelHost->dwAddr = dwIpAddr;

    /* Add the ARP entry */
    if (DeleteIpNetEntry(pDelHost) != NO_ERROR)
    {
        DoFormatMessage();
        goto cleanup;
    }

    HeapFree(GetProcessHeap(), 0, pDelHost);

    return EXIT_SUCCESS;

cleanup:
    if (pIpNetTable != NULL)
        HeapFree(GetProcessHeap(), 0, pIpNetTable);
    if (pDelHost != NULL)
        HeapFree(GetProcessHeap(), 0, pDelHost);
    return EXIT_FAILURE;
}