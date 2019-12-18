#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  KEVENT ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IoGetRelatedDeviceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TDI_SET_EVENT_HANDLER ; 
 int /*<<< orphan*/  TdiBuildInternalDeviceControlIrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TdiBuildSetEventHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TdiCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

NTSTATUS TdiSetEventHandler(
    PFILE_OBJECT FileObject,
    LONG EventType,
    PVOID Handler,
    PVOID Context)
/*
 * FUNCTION: Sets or resets an event handler
 * ARGUMENTS:
 *     FileObject = Pointer to file object
 *     EventType  = Event code
 *     Handler    = Event handler to be called when the event occurs
 *     Context    = Context input to handler when the event occurs
 * RETURNS:
 *     Status of operation
 * NOTES:
 *     Specify NULL for Handler to stop calling event handler
 */
{
    PDEVICE_OBJECT DeviceObject;
    IO_STATUS_BLOCK Iosb;
    KEVENT Event;
    PIRP Irp;

    AFD_DbgPrint(MAX_TRACE, ("Called\n"));

    if (!FileObject) {
        AFD_DbgPrint(MIN_TRACE, ("Bad file object.\n"));
        return STATUS_INVALID_PARAMETER;
    }

    DeviceObject = IoGetRelatedDeviceObject(FileObject);
    if (!DeviceObject) {
        AFD_DbgPrint(MIN_TRACE, ("Bad device object.\n"));
        return STATUS_INVALID_PARAMETER;
    }

    KeInitializeEvent(&Event, NotificationEvent, FALSE);

    Irp = TdiBuildInternalDeviceControlIrp(TDI_SET_EVENT_HANDLER,   /* Sub function */
                                           DeviceObject,            /* Device object */
                                           FileObject,              /* File object */
                                           &Event,                  /* Event */
                                           &Iosb);                  /* Status */
    if (!Irp)
        return STATUS_INSUFFICIENT_RESOURCES;



    TdiBuildSetEventHandler(Irp,
                            DeviceObject,
                            FileObject,
                            NULL,
                            NULL,
                            EventType,
                            Handler,
                            Context);

    return TdiCall(Irp, DeviceObject, &Event, &Iosb);
}