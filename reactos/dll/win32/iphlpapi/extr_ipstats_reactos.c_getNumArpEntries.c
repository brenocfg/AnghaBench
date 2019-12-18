#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tei_instance; } ;
typedef  TYPE_1__ TDIEntityID ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PMIB_IPNETROW ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  MIB_IPNETROW ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AT_ENTITY ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  FILE_READ_DATA ; 
 int /*<<< orphan*/  INFO_CLASS_PROTOCOL ; 
 int /*<<< orphan*/  INFO_TYPE_PROVIDER ; 
 int /*<<< orphan*/  IP_MIB_ARPTABLE_ENTRY_ID ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 scalar_t__ hasArp (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ isInterface (TYPE_1__*) ; 
 scalar_t__ openTcpFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdiFreeThingSet (TYPE_1__*) ; 
 scalar_t__ tdiGetEntityIDSet (int /*<<< orphan*/ ,TYPE_1__**,int*) ; 
 scalar_t__ tdiGetSetOfThings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 

DWORD getNumArpEntries(void)
{
    DWORD numEntities;
    TDIEntityID *entitySet = NULL;
    HANDLE tcpFile;
    int i, totalNumber = 0;
    NTSTATUS status;
    PMIB_IPNETROW IpArpTable = NULL;
    DWORD returnSize;

    TRACE("called.\n");

    status = openTcpFile( &tcpFile, FILE_READ_DATA );
    if( !NT_SUCCESS(status) ) {
        ERR("openTcpFile returned 0x%08lx\n", status);
        return 0;
    }

    status = tdiGetEntityIDSet( tcpFile, &entitySet, &numEntities );

    for( i = 0; i < numEntities; i++ ) {
        if( isInterface( &entitySet[i] ) &&
	    hasArp( tcpFile, &entitySet[i] ) ) {

	    status = tdiGetSetOfThings( tcpFile,
					INFO_CLASS_PROTOCOL,
					INFO_TYPE_PROVIDER,
					IP_MIB_ARPTABLE_ENTRY_ID,
					AT_ENTITY,
					entitySet[i].tei_instance,
					0,
					sizeof(MIB_IPNETROW),
					(PVOID *)&IpArpTable,
					&returnSize );

	    if( status == STATUS_SUCCESS ) totalNumber += returnSize;
		if( IpArpTable ) {
			tdiFreeThingSet( IpArpTable );
			IpArpTable = NULL;
		}
	}
    }

    closeTcpFile( tcpFile );
    if( entitySet ) tdiFreeThingSet( entitySet );
    return totalNumber;
}