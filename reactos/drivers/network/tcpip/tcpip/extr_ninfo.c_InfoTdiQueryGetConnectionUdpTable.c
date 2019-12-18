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
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_9__ {scalar_t__* OwningModuleInfo; scalar_t__ dwFlags; int /*<<< orphan*/  liCreateTimestamp; int /*<<< orphan*/  dwOwningPid; int /*<<< orphan*/  dwLocalPort; int /*<<< orphan*/  dwLocalAddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_7__ {TYPE_1__ Address; } ;
struct TYPE_8__ {scalar_t__ SubProcessTag; int /*<<< orphan*/  CreationTime; int /*<<< orphan*/  ProcessId; int /*<<< orphan*/  Port; TYPE_2__ Address; } ;
typedef  scalar_t__ TDI_TCPUDP_CLASS_INFO ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  PUINT ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  TYPE_3__* PADDRESS_FILE ;
typedef  int /*<<< orphan*/  MIB_UDPROW_OWNER_PID ;
typedef  TYPE_4__ MIB_UDPROW_OWNER_MODULE ;
typedef  int /*<<< orphan*/  MIB_UDPROW ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INFO ; 
 int /*<<< orphan*/  HandleToUlong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoCopyOut (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlZeroMemory (scalar_t__*,int) ; 
 int /*<<< orphan*/  TDI_INVALID_REQUEST ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TcpUdpClassOwner ; 
 scalar_t__ TcpUdpClassOwnerPid ; 

TDI_STATUS InfoTdiQueryGetConnectionUdpTable(PADDRESS_FILE AddrFile,
				    PNDIS_BUFFER Buffer,
				    PUINT BufferSize,
				    TDI_TCPUDP_CLASS_INFO Class)
{
    SIZE_T Size;
    MIB_UDPROW_OWNER_MODULE UdpRow;
    TDI_STATUS Status = TDI_INVALID_REQUEST;

    TI_DbgPrint(DEBUG_INFO, ("Called.\n"));

    if (Class == TcpUdpClassOwnerPid)
    {
        Size = sizeof(MIB_UDPROW_OWNER_PID);
    }
    else if (Class == TcpUdpClassOwner)
    {
        Size = sizeof(MIB_UDPROW_OWNER_MODULE);
    }
    else
    {
        Size = sizeof(MIB_UDPROW);
    }

    UdpRow.dwLocalAddr = AddrFile->Address.Address.IPv4Address;
    UdpRow.dwLocalPort = AddrFile->Port;
    UdpRow.dwOwningPid = HandleToUlong(AddrFile->ProcessId);
    UdpRow.liCreateTimestamp = AddrFile->CreationTime;
    UdpRow.dwFlags = 0; /* FIXME */
    if (Class == TcpUdpClassOwner)
    {
        RtlZeroMemory(&UdpRow.OwningModuleInfo[0], sizeof(UdpRow.OwningModuleInfo));
        UdpRow.OwningModuleInfo[0] = (ULONG_PTR)AddrFile->SubProcessTag;
    }

    Status = InfoCopyOut( (PCHAR)&UdpRow,
			  Size, Buffer, BufferSize );

    TI_DbgPrint(DEBUG_INFO, ("Returning %08x\n", Status));

    return Status;
}