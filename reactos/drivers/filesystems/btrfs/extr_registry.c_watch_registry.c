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
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ DelayedWorkQueue ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExInitializeWorkItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_NOTIFY_CHANGE_LAST_SET ; 
 int /*<<< orphan*/  ZwNotifyChangeKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  registry_work_item ; 
 int /*<<< orphan*/  wqi ; 

void watch_registry(HANDLE regh) {
    NTSTATUS Status;
    IO_STATUS_BLOCK iosb;

    ExInitializeWorkItem(&wqi, registry_work_item, regh);

    Status = ZwNotifyChangeKey(regh, NULL, (PVOID)&wqi, (PVOID)DelayedWorkQueue, &iosb, REG_NOTIFY_CHANGE_LAST_SET, true, NULL, 0, true);
    if (!NT_SUCCESS(Status))
        ERR("ZwNotifyChangeKey returned %08x\n", Status);
}