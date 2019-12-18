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
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  scalar_t__ DWORD64 ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

void kull_m_string_ptr_replace(PVOID ptr, DWORD64 size)
{
	PVOID tempPtr = NULL;
	if(size)
		if(tempPtr = LocalAlloc(LPTR, (SIZE_T) size))
			RtlCopyMemory(tempPtr, *(PVOID *) ptr, (size_t) size);
	*(PVOID *) ptr = tempPtr;
}