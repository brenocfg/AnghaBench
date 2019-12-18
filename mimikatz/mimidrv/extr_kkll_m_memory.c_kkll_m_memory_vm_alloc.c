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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  POOL_TAG ; 
 int /*<<< orphan*/  STATUS_DATA_NOT_ACCEPTED ; 
 int /*<<< orphan*/  STATUS_MEMORY_NOT_ALLOCATED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS kkll_m_memory_vm_alloc(DWORD Size, PVOID *Addr)
{
	NTSTATUS status = STATUS_DATA_NOT_ACCEPTED;
	if(Addr)
	{
		if(*Addr = ExAllocatePoolWithTag(NonPagedPool, Size, POOL_TAG))
			status = STATUS_SUCCESS;
		else
			status = STATUS_MEMORY_NOT_ALLOCATED;
	}
	return status;
}