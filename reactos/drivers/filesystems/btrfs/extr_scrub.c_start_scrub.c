#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int stopping; int paused; scalar_t__ thread; int /*<<< orphan*/  event; int /*<<< orphan*/  error; } ;
struct TYPE_6__ {scalar_t__ thread; } ;
struct TYPE_8__ {TYPE_2__ scrub; scalar_t__ readonly; TYPE_1__ balance; scalar_t__ locked; } ;
typedef  TYPE_3__ device_extension ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KPROCESSOR_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  OBJ_KERNEL_HANDLE ; 
 int /*<<< orphan*/  PsCreateSystemThread (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  RtlConvertLongToLuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SE_MANAGE_VOLUME_PRIVILEGE ; 
 int /*<<< orphan*/  STATUS_DEVICE_NOT_READY ; 
 int /*<<< orphan*/  STATUS_MEDIA_WRITE_PROTECTED ; 
 int /*<<< orphan*/  STATUS_PRIVILEGE_NOT_HELD ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SeSinglePrivilegeCheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  scrub_thread ; 

NTSTATUS start_scrub(device_extension* Vcb, KPROCESSOR_MODE processor_mode) {
    NTSTATUS Status;
    OBJECT_ATTRIBUTES oa;

    if (!SeSinglePrivilegeCheck(RtlConvertLongToLuid(SE_MANAGE_VOLUME_PRIVILEGE), processor_mode))
        return STATUS_PRIVILEGE_NOT_HELD;

    if (Vcb->locked) {
        WARN("cannot start scrub while locked\n");
        return STATUS_DEVICE_NOT_READY;
    }

    if (Vcb->balance.thread) {
        WARN("cannot start scrub while balance running\n");
        return STATUS_DEVICE_NOT_READY;
    }

    if (Vcb->scrub.thread) {
        WARN("scrub already running\n");
        return STATUS_DEVICE_NOT_READY;
    }

    if (Vcb->readonly)
        return STATUS_MEDIA_WRITE_PROTECTED;

    Vcb->scrub.stopping = false;
    Vcb->scrub.paused = false;
    Vcb->scrub.error = STATUS_SUCCESS;
    KeInitializeEvent(&Vcb->scrub.event, NotificationEvent, !Vcb->scrub.paused);

    InitializeObjectAttributes(&oa, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);

    Status = PsCreateSystemThread(&Vcb->scrub.thread, 0, &oa, NULL, NULL, scrub_thread, Vcb);
    if (!NT_SUCCESS(Status)) {
        ERR("PsCreateSystemThread returned %08x\n", Status);
        return Status;
    }

    return STATUS_SUCCESS;
}