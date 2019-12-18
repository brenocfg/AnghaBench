#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* dwForwardNextHop; int /*<<< orphan*/  dwForwardMetric1; void* dwForwardMask; void* dwForwardDest; } ;
typedef  char TCHAR ;
typedef  TYPE_1__* PMIB_IPFORWARDROW ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcscmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ttoi (char*) ; 
 void* inet_addr (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static int convert_add_cmd_line( PMIB_IPFORWARDROW RowToAdd,
              int argc, TCHAR **argv ) {
    int i;
#ifdef UNICODE
    char addr[16];
#endif

    if( argc > 1 )
    {
#ifdef UNICODE
        sprintf( addr, "%ls", argv[0] );
        RowToAdd->dwForwardDest = inet_addr( addr );
#else
        RowToAdd->dwForwardDest = inet_addr( argv[0] );
#endif
    }
    else
        return FALSE;
    for( i = 1; i < argc; i++ )
    {
        if( !_tcscmp( argv[i], _T("mask") ) )
        {
            i++; if( i >= argc ) return FALSE;
#ifdef UNICODE
            sprintf( addr, "%ls", argv[i] );
            RowToAdd->dwForwardMask = inet_addr( addr );
#else
            RowToAdd->dwForwardMask = inet_addr( argv[i] );
#endif
        }
        else if( !_tcscmp( argv[i], _T("metric") ) )
        {
            i++;
            if( i >= argc )
                return FALSE;
            RowToAdd->dwForwardMetric1 = _ttoi( argv[i] );
        }
        else
        {
#ifdef UNICODE
            sprintf( addr, "%ls", argv[i] );
            RowToAdd->dwForwardNextHop = inet_addr( addr );
#else
            RowToAdd->dwForwardNextHop = inet_addr( argv[i] );
#endif
        }
    }

    return TRUE;
}