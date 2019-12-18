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
struct TYPE_9__ {scalar_t__ QuadPart; } ;
struct TYPE_8__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_10__ {int paused; TYPE_2__ resume_time; TYPE_1__ duration; int /*<<< orphan*/  event; int /*<<< orphan*/  thread; } ;
struct TYPE_11__ {TYPE_3__ scrub; } ;
typedef  TYPE_4__ device_extension ;
struct TYPE_12__ {scalar_t__ QuadPart; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_5__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  KPROCESSOR_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  KeClearEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeQuerySystemTime (TYPE_5__*) ; 
 int /*<<< orphan*/  RtlConvertLongToLuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SE_MANAGE_VOLUME_PRIVILEGE ; 
 int /*<<< orphan*/  STATUS_DEVICE_NOT_READY ; 
 int /*<<< orphan*/  STATUS_PRIVILEGE_NOT_HELD ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SeSinglePrivilegeCheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS pause_scrub(device_extension* Vcb, KPROCESSOR_MODE processor_mode) {
    LARGE_INTEGER time;

    if (!SeSinglePrivilegeCheck(RtlConvertLongToLuid(SE_MANAGE_VOLUME_PRIVILEGE), processor_mode))
        return STATUS_PRIVILEGE_NOT_HELD;

    if (!Vcb->scrub.thread)
        return STATUS_DEVICE_NOT_READY;

    if (Vcb->scrub.paused)
        return STATUS_DEVICE_NOT_READY;

    Vcb->scrub.paused = true;
    KeClearEvent(&Vcb->scrub.event);

    KeQuerySystemTime(&time);
    Vcb->scrub.duration.QuadPart += time.QuadPart - Vcb->scrub.resume_time.QuadPart;

    return STATUS_SUCCESS;
}