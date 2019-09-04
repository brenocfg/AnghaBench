#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_11__ {int /*<<< orphan*/  String; } ;
struct TYPE_12__ {TYPE_1__ IpAddress; } ;
struct TYPE_14__ {unsigned int dwNumEntries; TYPE_3__* table; struct TYPE_14__* Next; int /*<<< orphan*/  Description; int /*<<< orphan*/  Index; TYPE_2__ GatewayList; } ;
struct TYPE_13__ {int /*<<< orphan*/  dwForwardMetric1; int /*<<< orphan*/  dwForwardIfIndex; int /*<<< orphan*/  dwForwardNextHop; int /*<<< orphan*/  dwForwardMask; int /*<<< orphan*/  dwForwardDest; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_4__* PMIB_IPFORWARDTABLE ;
typedef  TYPE_4__* PIP_ADAPTER_INFO ;
typedef  TYPE_4__ IP_ADAPTER_INFO ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_BUFFER_OVERFLOW ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 int ERROR_SUCCESS ; 
 scalar_t__ GetAdaptersInfo (TYPE_4__*,int*) ; 
 scalar_t__ GetIpForwardTable (TYPE_4__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_ADDR_OF (int /*<<< orphan*/ ) ; 
 int IPBUF ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _stprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int PrintRoutes()
{
    PMIB_IPFORWARDTABLE IpForwardTable = NULL;
    PIP_ADAPTER_INFO pAdapterInfo = NULL;
    ULONG Size = 0;
    DWORD Error = 0;
    ULONG adaptOutBufLen = sizeof(IP_ADAPTER_INFO);
    TCHAR DefGate[16];
    TCHAR Destination[IPBUF], Gateway[IPBUF], Netmask[IPBUF];
    unsigned int i;

    /* set required buffer size */
    pAdapterInfo = (IP_ADAPTER_INFO *) malloc( adaptOutBufLen );
    if (pAdapterInfo == NULL)
    {
        Error = ERROR_NOT_ENOUGH_MEMORY;
        goto Error;
    }
    if (GetAdaptersInfo( pAdapterInfo, &adaptOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
       free (pAdapterInfo);
       pAdapterInfo = (IP_ADAPTER_INFO *) malloc (adaptOutBufLen);
       if (pAdapterInfo == NULL)
       {
           Error = ERROR_NOT_ENOUGH_MEMORY;
           goto Error;
       }
    }

    if( (GetIpForwardTable( NULL, &Size, TRUE )) == ERROR_INSUFFICIENT_BUFFER )
    {
        if (!(IpForwardTable = malloc( Size )))
        {
            Error = ERROR_NOT_ENOUGH_MEMORY;
            goto Error;
        }
    }

    if (((Error = GetAdaptersInfo(pAdapterInfo, &adaptOutBufLen)) == NO_ERROR) &&
        ((Error = GetIpForwardTable(IpForwardTable, &Size, TRUE)) == NO_ERROR))
    {
        _stprintf(DefGate,
#ifdef UNICODE
                  _T("%hs"),
#else
                  _T("%s"),
#endif
                  pAdapterInfo->GatewayList.IpAddress.String);
        _tprintf(_T("===========================================================================\n"));
        _tprintf(_T("Interface List\n"));
        /* FIXME - sort by the index! */
        while (pAdapterInfo)
        {
#ifdef UNICODE
            _tprintf(_T("0x%lu ........................... %hs\n"),
#else
            _tprintf(_T("0x%lu ........................... %s\n"),
#endif
                     pAdapterInfo->Index, pAdapterInfo->Description);
            pAdapterInfo = pAdapterInfo->Next;
        }
        _tprintf(_T("===========================================================================\n"));

        _tprintf(_T("===========================================================================\n"));
        _tprintf(_T("Active Routes:\n"));
        _tprintf( _T("%-27s%-17s%-14s%-11s%-10s\n"),
                  _T("Network Destination"),
                  _T("Netmask"),
                  _T("Gateway"),
                  _T("Interface"),
                  _T("Metric") );
        for( i = 0; i < IpForwardTable->dwNumEntries; i++ )
        {
            _stprintf( Destination,
#ifdef UNICODE
                       _T("%hs"),
#else
                       _T("%s"),
#endif
                       inet_ntoa( IN_ADDR_OF(IpForwardTable->table[i].dwForwardDest) ) );
            _stprintf( Netmask,
#ifdef UNICODE
                       _T("%hs"),
#else
                       _T("%s"),
#endif
                       inet_ntoa( IN_ADDR_OF(IpForwardTable->table[i].dwForwardMask) ) );
            _stprintf( Gateway,
#ifdef UNICODE
                       _T("%hs"),
#else
                       _T("%s"),
#endif
                       inet_ntoa( IN_ADDR_OF(IpForwardTable->table[i].dwForwardNextHop) ) );

            _tprintf( _T("%17s%17s%17s%16ld%9ld\n"),
                      Destination,
                      Netmask,
                      Gateway,
                      IpForwardTable->table[i].dwForwardIfIndex,
                      IpForwardTable->table[i].dwForwardMetric1 );
        }
        _tprintf(_T("Default Gateway:%18s\n"), DefGate);
        _tprintf(_T("===========================================================================\n"));
        _tprintf(_T("Persistent Routes:\n"));

        free(IpForwardTable);
        free(pAdapterInfo);

        return ERROR_SUCCESS;
    }
    else
    {
Error:
        if (pAdapterInfo) free(pAdapterInfo);
        if (IpForwardTable) free(IpForwardTable);
        _ftprintf( stderr, _T("Route enumerate failed\n") );
        return Error;
    }
}