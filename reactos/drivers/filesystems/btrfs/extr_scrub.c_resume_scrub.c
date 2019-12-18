#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int paused; int /*<<< orphan*/  resume_time; int /*<<< orphan*/  event; int /*<<< orphan*/  thread; } ;
struct TYPE_5__ {TYPE_1__ scrub; } ;
typedef  TYPE_2__ device_extension ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KPROCESSOR_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  KeQuerySystemTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlConvertLongToLuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SE_MANAGE_VOLUME_PRIVILEGE ; 
 int /*<<< orphan*/  STATUS_DEVICE_NOT_READY ; 
 int /*<<< orphan*/  STATUS_PRIVILEGE_NOT_HELD ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SeSinglePrivilegeCheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS resume_scrub(device_extension* Vcb, KPROCESSOR_MODE processor_mode) {
    if (!SeSinglePrivilegeCheck(RtlConvertLongToLuid(SE_MANAGE_VOLUME_PRIVILEGE), processor_mode))
        return STATUS_PRIVILEGE_NOT_HELD;

    if (!Vcb->scrub.thread)
        return STATUS_DEVICE_NOT_READY;

    if (!Vcb->scrub.paused)
        return STATUS_DEVICE_NOT_READY;

    Vcb->scrub.paused = false;
    KeSetEvent(&Vcb->scrub.event, 0, false);

    KeQuerySystemTime(&Vcb->scrub.resume_time);

    return STATUS_SUCCESS;
}