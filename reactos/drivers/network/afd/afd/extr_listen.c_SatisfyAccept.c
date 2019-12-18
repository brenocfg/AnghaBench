#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ RemoteAddress; int /*<<< orphan*/  ConnectReturnInfo; int /*<<< orphan*/  ConnectCallInfo; int /*<<< orphan*/  Connection; } ;
struct TYPE_12__ {TYPE_1__* ConnInfo; int /*<<< orphan*/  Object; } ;
struct TYPE_11__ {TYPE_4__* FsContext; } ;
struct TYPE_10__ {int /*<<< orphan*/  RemoteAddress; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_2__* PFILE_OBJECT ;
typedef  TYPE_3__* PAFD_TDI_OBJECT_QELT ;
typedef  TYPE_4__* PAFD_FCB ;
typedef  int /*<<< orphan*/  PAFD_DEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LostSocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  MakeSocketIntoConnection (TYPE_4__*) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  SocketAcquireStateLock (TYPE_4__*) ; 
 int /*<<< orphan*/  TAG_AFD_TRANSPORT_ADDRESS ; 
 scalar_t__ TaCopyTransportAddress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TdiBuildConnectionInfo (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockAndMaybeComplete (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS SatisfyAccept( PAFD_DEVICE_EXTENSION DeviceExt,
                               PIRP Irp,
                               PFILE_OBJECT NewFileObject,
                               PAFD_TDI_OBJECT_QELT Qelt ) {
    PAFD_FCB FCB = NewFileObject->FsContext;
    NTSTATUS Status;

    UNREFERENCED_PARAMETER(DeviceExt);

    if( !SocketAcquireStateLock( FCB ) )
        return LostSocket( Irp );

    /* Transfer the connection to the new socket, launch the opening read */
    AFD_DbgPrint(MID_TRACE,("Completing a real accept (FCB %p)\n", FCB));

    FCB->Connection = Qelt->Object;

    if (FCB->RemoteAddress)
    {
        ExFreePoolWithTag(FCB->RemoteAddress, TAG_AFD_TRANSPORT_ADDRESS);
    }

    FCB->RemoteAddress =
        TaCopyTransportAddress( Qelt->ConnInfo->RemoteAddress );

    if( !FCB->RemoteAddress )
        Status = STATUS_NO_MEMORY;
    else
        Status = MakeSocketIntoConnection( FCB );

    if (NT_SUCCESS(Status))
        Status = TdiBuildConnectionInfo(&FCB->ConnectCallInfo, FCB->RemoteAddress);

    if (NT_SUCCESS(Status))
        Status = TdiBuildConnectionInfo(&FCB->ConnectReturnInfo, FCB->RemoteAddress);

    return UnlockAndMaybeComplete( FCB, Status, Irp, 0 );
}