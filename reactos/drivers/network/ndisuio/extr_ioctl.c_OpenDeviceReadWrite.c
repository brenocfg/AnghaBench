#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  Buffer; scalar_t__ Length; scalar_t__ MaximumLength; } ;
typedef  TYPE_5__ UNICODE_STRING ;
typedef  scalar_t__ ULONG ;
struct TYPE_21__ {scalar_t__ InputBufferLength; } ;
struct TYPE_22__ {TYPE_1__ DeviceIoControl; } ;
struct TYPE_29__ {TYPE_2__ Parameters; TYPE_10__* FileObject; } ;
struct TYPE_24__ {scalar_t__ Information; int /*<<< orphan*/  Status; } ;
struct TYPE_23__ {int /*<<< orphan*/  SystemBuffer; } ;
struct TYPE_28__ {TYPE_4__ IoStatus; TYPE_3__ AssociatedIrp; } ;
struct TYPE_27__ {scalar_t__ OpenCount; int /*<<< orphan*/  Spinlock; int /*<<< orphan*/  OpenEntryList; int /*<<< orphan*/  DeviceName; } ;
struct TYPE_26__ {int /*<<< orphan*/  ListEntry; int /*<<< orphan*/  WriteOnly; TYPE_10__* FileObject; } ;
struct TYPE_20__ {TYPE_6__* FsContext2; TYPE_7__* FsContext; } ;
typedef  TYPE_6__* PNDISUIO_OPEN_ENTRY ;
typedef  TYPE_7__* PNDISUIO_ADAPTER_CONTEXT ;
typedef  TYPE_8__* PIRP ;
typedef  TYPE_9__* PIO_STACK_LOCATION ;
typedef  TYPE_10__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DereferenceAdapterContextWithOpenEntry (TYPE_7__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_7__* FindAdapterContextByName (TYPE_5__*) ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  ReferenceAdapterContext (TYPE_7__*) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static
NTSTATUS
OpenDeviceReadWrite(PIRP Irp, PIO_STACK_LOCATION IrpSp)
{
    PFILE_OBJECT FileObject = IrpSp->FileObject;
    UNICODE_STRING DeviceName;
    ULONG NameLength;
    NTSTATUS Status;
    PNDISUIO_ADAPTER_CONTEXT AdapterContext;
    PNDISUIO_OPEN_ENTRY OpenEntry;
    KIRQL OldIrql;

    NameLength = IrpSp->Parameters.DeviceIoControl.InputBufferLength;
    if (NameLength != 0)
    {
        DeviceName.MaximumLength = DeviceName.Length = NameLength;
        DeviceName.Buffer = Irp->AssociatedIrp.SystemBuffer;

        /* Check if this already has a context */
        AdapterContext = FindAdapterContextByName(&DeviceName);
        if (AdapterContext != NULL)
        {
            DPRINT("Binding file object 0x%x to device %wZ\n", FileObject, &AdapterContext->DeviceName);

            /* Reference the adapter context */
            KeAcquireSpinLock(&AdapterContext->Spinlock, &OldIrql);
            if (AdapterContext->OpenCount != 0)
            {
                /* An open for read-write is exclusive,
                 * so we can't have any other open handles */
                KeReleaseSpinLock(&AdapterContext->Spinlock, OldIrql);
                Status = STATUS_INVALID_PARAMETER;
            }
            else
            {
                /* Add a reference */
                ReferenceAdapterContext(AdapterContext);
                Status = STATUS_SUCCESS;
            }
        }
        else
        {
            /* Invalid device name */
            Status = STATUS_INVALID_PARAMETER;
        }

        /* Check that the bind succeeded */
        if (NT_SUCCESS(Status))
        {
            OpenEntry = ExAllocatePool(NonPagedPool, sizeof(*OpenEntry));
            if (OpenEntry)
            {
                /* Set the file object pointer */
                OpenEntry->FileObject = FileObject;
                
                /* Set the permissions */
                OpenEntry->WriteOnly = FALSE;

                /* Associate this FO with the adapter */
                FileObject->FsContext = AdapterContext;
                FileObject->FsContext2 = OpenEntry;

                /* Add it to the adapter's list */
                InsertTailList(&AdapterContext->OpenEntryList,
                               &OpenEntry->ListEntry);

                /* Success */
                KeReleaseSpinLock(&AdapterContext->Spinlock, OldIrql);
                Status = STATUS_SUCCESS;
            }
            else
            {
                /* Remove the reference we added */
                KeReleaseSpinLock(&AdapterContext->Spinlock, OldIrql);
                DereferenceAdapterContextWithOpenEntry(AdapterContext, NULL);
                Status = STATUS_NO_MEMORY;
            }
        }
    }
    else
    {
        /* Invalid device name */
        Status = STATUS_INVALID_PARAMETER;
    }
    
    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = 0;
    
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    
    return Status;
}