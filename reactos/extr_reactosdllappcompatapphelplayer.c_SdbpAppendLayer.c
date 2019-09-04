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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__* PWSTR ;
typedef  int PCWSTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int SPACE_ONLY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  StringCbCatNW (scalar_t__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  StringCbCatW (scalar_t__*,int /*<<< orphan*/ ,int) ; 

BOOL SdbpAppendLayer(PWSTR target, DWORD len, PCWSTR layer, PCWSTR end)
{
    NTSTATUS Status = STATUS_SUCCESS;
    if (target[0])
        Status = StringCbCatW(target, len, SPACE_ONLY);

    if (NT_SUCCESS(Status))
    {
        if (end)
            Status = StringCbCatNW(target, len, layer, (end - layer) * sizeof(WCHAR));
        else
            Status = StringCbCatW(target, len, layer);
    }

    return NT_SUCCESS(Status);
}