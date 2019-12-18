#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  address; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/ * PKULL_M_MEMORY_HANDLE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ KULL_M_MEMORY_ADDRESS ;
typedef  scalar_t__ DWORD32 ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  KULL_M_MEMORY_GLOBAL_OWN_HANDLE ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/  LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ULongToPtr (scalar_t__) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ kull_m_memory_copy (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kuhl_m_crypto_extractor_bcrypt32_classic(PKULL_M_MEMORY_HANDLE hMemory, DWORD32 addr, DWORD size, LPCWSTR num)
{
	KULL_M_MEMORY_ADDRESS address = {ULongToPtr(addr), hMemory}, aLocalBuffer = {NULL, &KULL_M_MEMORY_GLOBAL_OWN_HANDLE};

	if(addr && size)
	{
		kprintf(L"%s: ", num);
		if(aLocalBuffer.address = LocalAlloc(LPTR, size))
		{
			if(kull_m_memory_copy(&aLocalBuffer, &address, size))
				kull_m_string_wprintf_hex(aLocalBuffer.address, size, 0);
			LocalFree(aLocalBuffer.address);
		}
		kprintf(L"\n");
	}
}