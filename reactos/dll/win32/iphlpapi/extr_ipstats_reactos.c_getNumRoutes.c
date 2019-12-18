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
typedef  int /*<<< orphan*/  isnmp ;
struct TYPE_4__ {int ipsi_numroutes; } ;
typedef  int /*<<< orphan*/  TDIEntityID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ IPSNMPInfo ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  FILE_READ_DATA ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 scalar_t__ isIpEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  openTcpFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdiFreeThingSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdiGetEntityIDSet (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  tdiGetMibForIpEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

DWORD getNumRoutes(void)
{
    DWORD numEntities, numRoutes = 0;
    TDIEntityID *entitySet;
    HANDLE tcpFile;
    int i;
    NTSTATUS status;

    TRACE("called.\n");

    status = openTcpFile( &tcpFile, FILE_READ_DATA );
    if( !NT_SUCCESS(status) ) {
        ERR("openTcpFile returned 0x%08lx\n", status);
        return 0;
    }

    status = tdiGetEntityIDSet( tcpFile, &entitySet, &numEntities );
    if( !NT_SUCCESS(status) ) {
        ERR("tdiGetEntityIDSet returned 0x%08lx\n", status);
        closeTcpFile( tcpFile );
        return 0;
    }

    for( i = 0; i < numEntities; i++ ) {
        if( isIpEntity( tcpFile, &entitySet[i] ) ) {
            IPSNMPInfo isnmp;
            memset( &isnmp, 0, sizeof( isnmp ) );
            status = tdiGetMibForIpEntity( tcpFile, &entitySet[i], &isnmp );
            if( !NT_SUCCESS(status) ) {
                ERR("tdiGetMibForIpEntity returned 0x%08lx, for i = %d", status, i);
                numRoutes = 0;
                break;
            }
            numRoutes += isnmp.ipsi_numroutes;
        }
    }

    TRACE("numRoutes = %lu\n", numRoutes);

    tdiFreeThingSet( entitySet );
    closeTcpFile( tcpFile );

    return numRoutes;
}