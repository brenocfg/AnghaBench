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
typedef  int /*<<< orphan*/  wow64_ptr ;
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int ACCESS_MASK ;

/* Variables and functions */
 int KEY_WOW64_64KEY ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtQueryInformationProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessWow64Information ; 
 int g_QueryFlag ; 

ACCESS_MASK Wow64QueryFlag(void)
{
    if (g_QueryFlag == 0xffffffff)
    {
        ULONG_PTR wow64_ptr = 0;
        NTSTATUS Status = NtQueryInformationProcess(NtCurrentProcess(), ProcessWow64Information, &wow64_ptr, sizeof(wow64_ptr), NULL);
        g_QueryFlag = (NT_SUCCESS(Status) && wow64_ptr != 0) ? KEY_WOW64_64KEY : 0;
    }
    return g_QueryFlag;
}