#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_36__ {TYPE_6__* FsContext; } ;
struct TYPE_29__ {int FileInformationClass; scalar_t__ Length; } ;
struct TYPE_30__ {TYPE_2__ QueryFile; } ;
struct TYPE_35__ {TYPE_3__ Parameters; } ;
struct TYPE_31__ {scalar_t__ Information; } ;
struct TYPE_28__ {int /*<<< orphan*/  SystemBuffer; } ;
struct TYPE_34__ {TYPE_4__ IoStatus; TYPE_1__ AssociatedIrp; } ;
struct TYPE_33__ {int /*<<< orphan*/  MainResource; } ;
struct TYPE_32__ {int /*<<< orphan*/  Flags; TYPE_9__* FileObject; TYPE_10__* DeviceObject; TYPE_8__* Stack; TYPE_7__* Irp; } ;
struct TYPE_27__ {int /*<<< orphan*/  DeviceExtension; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_5__* PNTFS_IRP_CONTEXT ;
typedef  TYPE_6__* PNTFS_FCB ;
typedef  TYPE_7__* PIRP ;
typedef  TYPE_8__* PIO_STACK_LOCATION ;
typedef  TYPE_9__* PFILE_OBJECT ;
typedef  TYPE_10__* PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int FILE_INFORMATION_CLASS ;

/* Variables and functions */
 int /*<<< orphan*/  BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,TYPE_5__*) ; 
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
#define  FileAllInformation 136 
#define  FileAlternateNameInformation 135 
#define  FileBasicInformation 134 
#define  FileInternalInformation 133 
#define  FileNameInformation 132 
#define  FileNetworkOpenInformation 131 
#define  FilePositionInformation 130 
#define  FileStandardInformation 129 
#define  FileStreamInformation 128 
 TYPE_5__* GetInfoClassName (int) ; 
 int /*<<< orphan*/  IRPCONTEXT_CANWAIT ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsGetBasicInformation (TYPE_9__*,TYPE_6__*,TYPE_10__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NtfsGetInternalInformation (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NtfsGetNameInformation (TYPE_9__*,TYPE_6__*,TYPE_10__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NtfsGetNetworkOpenInformation (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NtfsGetPositionInformation (TYPE_9__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NtfsGetStandardInformation (TYPE_6__*,TYPE_10__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NtfsGetSteamInformation (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  NtfsMarkIrpContextForQueue (TYPE_5__*) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
NtfsQueryInformation(PNTFS_IRP_CONTEXT IrpContext)
{
    FILE_INFORMATION_CLASS FileInformationClass;
    PIO_STACK_LOCATION Stack;
    PFILE_OBJECT FileObject;
    PNTFS_FCB Fcb;
    PVOID SystemBuffer;
    ULONG BufferLength;
    PIRP Irp;
    PDEVICE_OBJECT DeviceObject;
    NTSTATUS Status = STATUS_SUCCESS;

    DPRINT1("NtfsQueryInformation(%p)\n", IrpContext);

    Irp = IrpContext->Irp;
    Stack = IrpContext->Stack;
    DeviceObject = IrpContext->DeviceObject;
    FileInformationClass = Stack->Parameters.QueryFile.FileInformationClass;
    FileObject = IrpContext->FileObject;
    Fcb = FileObject->FsContext;

    SystemBuffer = Irp->AssociatedIrp.SystemBuffer;
    BufferLength = Stack->Parameters.QueryFile.Length;

    if (!ExAcquireResourceSharedLite(&Fcb->MainResource,
                                     BooleanFlagOn(IrpContext->Flags, IRPCONTEXT_CANWAIT)))
    {
        return NtfsMarkIrpContextForQueue(IrpContext);
    }

    switch (FileInformationClass)
    {
        case FileStandardInformation:
            Status = NtfsGetStandardInformation(Fcb,
                                                DeviceObject,
                                                SystemBuffer,
                                                &BufferLength);
            break;

        case FilePositionInformation:
            Status = NtfsGetPositionInformation(FileObject,
                                                SystemBuffer,
                                                &BufferLength);
            break;

        case FileBasicInformation:
            Status = NtfsGetBasicInformation(FileObject,
                                             Fcb,
                                             DeviceObject,
                                             SystemBuffer,
                                             &BufferLength);
            break;

        case FileNameInformation:
            Status = NtfsGetNameInformation(FileObject,
                                            Fcb,
                                            DeviceObject,
                                            SystemBuffer,
                                            &BufferLength);
            break;

        case FileInternalInformation:
            Status = NtfsGetInternalInformation(Fcb,
                                                SystemBuffer,
                                                &BufferLength);
            break;

        case FileNetworkOpenInformation:
            Status = NtfsGetNetworkOpenInformation(Fcb,
                                                   DeviceObject->DeviceExtension,
                                                   SystemBuffer,
                                                   &BufferLength);
            break;

        case FileStreamInformation:
            Status = NtfsGetSteamInformation(Fcb,
                                             DeviceObject->DeviceExtension,
                                             SystemBuffer,
                                             &BufferLength);
            break;

        case FileAlternateNameInformation:
        case FileAllInformation:
            DPRINT1("Unimplemented information class: %s\n", GetInfoClassName(FileInformationClass));
            Status = STATUS_NOT_IMPLEMENTED;
            break;

        default:
            DPRINT1("Unimplemented information class: %s\n", GetInfoClassName(FileInformationClass));
            Status = STATUS_INVALID_PARAMETER;
    }

    ExReleaseResourceLite(&Fcb->MainResource);

    if (NT_SUCCESS(Status))
        Irp->IoStatus.Information =
            Stack->Parameters.QueryFile.Length - BufferLength;
    else
        Irp->IoStatus.Information = 0;

    return Status;
}