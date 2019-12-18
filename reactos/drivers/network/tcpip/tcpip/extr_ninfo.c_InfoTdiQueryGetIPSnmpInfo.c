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
typedef  void* UINT ;
struct TYPE_3__ {int ipsi_numaddr; void* ipsi_numroutes; void* ipsi_numif; } ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  int /*<<< orphan*/  TDIEntityID ;
typedef  int /*<<< orphan*/  SnmpInfo ;
typedef  int /*<<< orphan*/  PUINT ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  int /*<<< orphan*/  PIP_INTERFACE ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  TYPE_1__ IPSNMPInfo ;

/* Variables and functions */
 void* CountFIBs (int /*<<< orphan*/ ) ; 
 void* CountInterfaces () ; 
 int /*<<< orphan*/  DEBUG_INFO ; 
 int /*<<< orphan*/  InfoCopyOut (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TDI_INVALID_REQUEST ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

TDI_STATUS InfoTdiQueryGetIPSnmpInfo( TDIEntityID ID,
                                      PIP_INTERFACE IF,
				      PNDIS_BUFFER Buffer,
				      PUINT BufferSize ) {
    IPSNMPInfo SnmpInfo;
    UINT IfCount = CountInterfaces();
    UINT RouteCount = CountFIBs(IF);
    TDI_STATUS Status = TDI_INVALID_REQUEST;

    TI_DbgPrint(DEBUG_INFO, ("Called.\n"));

    RtlZeroMemory(&SnmpInfo, sizeof(SnmpInfo));

    SnmpInfo.ipsi_numif = IfCount;
    SnmpInfo.ipsi_numaddr = 1;
    SnmpInfo.ipsi_numroutes = RouteCount;

    Status = InfoCopyOut( (PCHAR)&SnmpInfo, sizeof(SnmpInfo),
			  Buffer, BufferSize );

    TI_DbgPrint(DEBUG_INFO, ("Returning %08x\n", Status));

    return Status;
}