#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  if_operstatus; int /*<<< orphan*/  if_mtu; } ;
struct TYPE_8__ {TYPE_2__ ent; } ;
struct TYPE_6__ {int /*<<< orphan*/  iae_mask; int /*<<< orphan*/  iae_bcastaddr; int /*<<< orphan*/  iae_addr; } ;
struct TYPE_9__ {TYPE_3__ if_info; TYPE_1__ ip_addr; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int IPHLPAddrType ;
typedef  TYPE_4__ IFInfo ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_READ_DATA ; 
#define  IFMtu 132 
#define  IFStatus 131 
 int /*<<< orphan*/  INADDR_ANY ; 
#define  IPAAddr 130 
#define  IPABcast 129 
#define  IPAMask 128 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  closeTcpFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getIPAddrEntryForIf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  openTcpFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

DWORD getAddrByIndexOrName( char *name, DWORD index, IPHLPAddrType addrType ) {
    IFInfo ifInfo;
    HANDLE tcpFile;
    NTSTATUS status = STATUS_SUCCESS;
    DWORD addrOut = INADDR_ANY;

    status = openTcpFile( &tcpFile, FILE_READ_DATA );

    if( NT_SUCCESS(status) ) {
        status = getIPAddrEntryForIf( tcpFile, name, index, &ifInfo );
        if( NT_SUCCESS(status) ) {
            switch( addrType ) {
            case IPAAddr:  addrOut = ifInfo.ip_addr.iae_addr; break;
            case IPABcast: addrOut = ifInfo.ip_addr.iae_bcastaddr; break;
            case IPAMask:  addrOut = ifInfo.ip_addr.iae_mask; break;
            case IFMtu:    addrOut = ifInfo.if_info.ent.if_mtu; break;
            case IFStatus: addrOut = ifInfo.if_info.ent.if_operstatus; break;
            }
        }
        closeTcpFile( tcpFile );
    }

    return addrOut;
}