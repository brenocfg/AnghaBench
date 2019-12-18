#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_19__ {int InputBufferLength; } ;
struct TYPE_20__ {TYPE_2__ DeviceIoControl; } ;
struct TYPE_26__ {TYPE_3__ Parameters; } ;
struct TYPE_21__ {int Information; int /*<<< orphan*/  Status; } ;
struct TYPE_18__ {TYPE_5__* SystemBuffer; } ;
struct TYPE_25__ {TYPE_4__ IoStatus; TYPE_1__ AssociatedIrp; } ;
struct TYPE_24__ {struct TYPE_24__* Flink; } ;
struct TYPE_17__ {int Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_23__ {TYPE_14__ DeviceName; } ;
struct TYPE_22__ {int BindingIndex; int DeviceNameOffset; int DeviceNameLength; int DeviceDescrOffset; scalar_t__ DeviceDescrLength; } ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_5__* PNDISUIO_QUERY_BINDING ;
typedef  TYPE_6__* PNDISUIO_ADAPTER_CONTEXT ;
typedef  TYPE_7__* PLIST_ENTRY ;
typedef  TYPE_8__* PIRP ;
typedef  TYPE_9__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  NDISUIO_QUERY_BINDING ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 TYPE_6__* CONTAINING_RECORD (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,int,TYPE_14__*) ; 
 TYPE_7__ GlobalAdapterList ; 
 int /*<<< orphan*/  GlobalAdapterListLock ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  NDISUIO_ADAPTER_CONTEXT ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_NO_MORE_ENTRIES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static
NTSTATUS
QueryBinding(PIRP Irp, PIO_STACK_LOCATION IrpSp)
{
    PNDISUIO_ADAPTER_CONTEXT AdapterContext = NULL;
    PNDISUIO_QUERY_BINDING QueryBinding = Irp->AssociatedIrp.SystemBuffer;
    ULONG BindingLength = IrpSp->Parameters.DeviceIoControl.InputBufferLength;
    NTSTATUS Status;
    PLIST_ENTRY CurrentEntry;
    KIRQL OldIrql;
    ULONG i;
    ULONG BytesCopied = 0;

    if (QueryBinding && BindingLength >= sizeof(NDISUIO_QUERY_BINDING))
    {
        KeAcquireSpinLock(&GlobalAdapterListLock, &OldIrql);
        i = 0;
        CurrentEntry = GlobalAdapterList.Flink;
        while (CurrentEntry != &GlobalAdapterList)
        {
            if (i == QueryBinding->BindingIndex)
            {
                AdapterContext = CONTAINING_RECORD(CurrentEntry, NDISUIO_ADAPTER_CONTEXT, ListEntry);
                break;
            }
            i++;
            CurrentEntry = CurrentEntry->Flink;
        }
        KeReleaseSpinLock(&GlobalAdapterListLock, OldIrql);
        if (AdapterContext)
        {
            DPRINT("Query binding for index %d is adapter %wZ\n", i, &AdapterContext->DeviceName);
            BytesCopied = sizeof(NDISUIO_QUERY_BINDING);
            if (AdapterContext->DeviceName.Length <= BindingLength - BytesCopied)
            {
                QueryBinding->DeviceNameOffset = BytesCopied;
                QueryBinding->DeviceNameLength = AdapterContext->DeviceName.Length;
                RtlCopyMemory((PUCHAR)QueryBinding + QueryBinding->DeviceNameOffset,
                              AdapterContext->DeviceName.Buffer,
                              QueryBinding->DeviceNameLength);
                BytesCopied += AdapterContext->DeviceName.Length;

                /* FIXME: Copy description too */
                QueryBinding->DeviceDescrOffset = BytesCopied;
                QueryBinding->DeviceDescrLength = 0;
                
                /* Successful */
                Status = STATUS_SUCCESS;
            }
            else
            {
                /* Not enough buffer space */
                Status = STATUS_BUFFER_TOO_SMALL;
            }
        }
        else
        {
            /* Invalid index */
            Status = STATUS_NO_MORE_ENTRIES;
        }
    }
    else
    {
        /* Invalid parameters */
        Status = STATUS_INVALID_PARAMETER;
    }
    
    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = BytesCopied;
    
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    
    return Status;
}