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
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePoolWithTag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POOL_TAG ; 
 int /*<<< orphan*/  STATUS_DATA_NOT_ACCEPTED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS kkll_m_memory_vm_free(PVOID Addr)
{
	NTSTATUS status = STATUS_DATA_NOT_ACCEPTED;
	if(Addr)
	{
		ExFreePoolWithTag(Addr, POOL_TAG);
		status = STATUS_SUCCESS;
	}
	return status;
}