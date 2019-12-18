#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t datalen; int /*<<< orphan*/  buffer_event; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ send_context ;
struct TYPE_10__ {int /*<<< orphan*/  send_load_lock; } ;
typedef  TYPE_3__ device_extension ;
struct TYPE_11__ {TYPE_1__* send; int /*<<< orphan*/  send_status; } ;
typedef  TYPE_4__ ccb ;
typedef  size_t ULONG_PTR ;
typedef  size_t ULONG ;
struct TYPE_12__ {TYPE_4__* FsContext2; } ;
struct TYPE_8__ {int /*<<< orphan*/  cleared_event; scalar_t__ context; } ;
typedef  TYPE_5__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KPROCESSOR_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  KeClearEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KeWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlConvertLongToLuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlMoveMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  SE_MANAGE_VOLUME_PRIVILEGE ; 
 int /*<<< orphan*/  STATUS_END_OF_FILE ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_PRIVILEGE_NOT_HELD ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SeSinglePrivilegeCheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (size_t,size_t) ; 

NTSTATUS read_send_buffer(device_extension* Vcb, PFILE_OBJECT FileObject, void* data, ULONG datalen, ULONG_PTR* retlen, KPROCESSOR_MODE processor_mode) {
    ccb* ccb;
    send_context* context;

    ccb = FileObject ? FileObject->FsContext2 : NULL;
    if (!ccb)
        return STATUS_INVALID_PARAMETER;

    if (!SeSinglePrivilegeCheck(RtlConvertLongToLuid(SE_MANAGE_VOLUME_PRIVILEGE), processor_mode))
        return STATUS_PRIVILEGE_NOT_HELD;

    ExAcquireResourceExclusiveLite(&Vcb->send_load_lock, true);

    if (!ccb->send) {
        ExReleaseResourceLite(&Vcb->send_load_lock);
        return !NT_SUCCESS(ccb->send_status) ? ccb->send_status : STATUS_END_OF_FILE;
    }

    context = (send_context*)ccb->send->context;

    KeWaitForSingleObject(&context->buffer_event, Executive, KernelMode, false, NULL);

    if (datalen == 0) {
        ExReleaseResourceLite(&Vcb->send_load_lock);
        return STATUS_SUCCESS;
    }

    RtlCopyMemory(data, context->data, min(datalen, context->datalen));

    if (datalen < context->datalen) { // not empty yet
        *retlen = datalen;
        RtlMoveMemory(context->data, &context->data[datalen], context->datalen - datalen);
        context->datalen -= datalen;
        ExReleaseResourceLite(&Vcb->send_load_lock);
    } else {
        *retlen = context->datalen;
        context->datalen = 0;
        ExReleaseResourceLite(&Vcb->send_load_lock);

        KeClearEvent(&context->buffer_event);
        KeSetEvent(&ccb->send->cleared_event, 0, false);
    }

    return STATUS_SUCCESS;
}