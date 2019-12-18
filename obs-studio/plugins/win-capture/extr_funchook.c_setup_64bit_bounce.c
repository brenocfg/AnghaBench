#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  intptr_t uint64_t ;
typedef  scalar_t__ uint32_t ;
struct func_hook {int func_addr; intptr_t hook_addr; int is_64bit_jump; void* bounce_addr; } ;
typedef  int /*<<< orphan*/  mbi ;
struct TYPE_6__ {uintptr_t RegionSize; scalar_t__ AllocationBase; } ;
struct TYPE_5__ {scalar_t__ dwAllocationGranularity; } ;
typedef  TYPE_1__ SYSTEM_INFO ;
typedef  TYPE_2__ MEMORY_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/  LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  FillMemory (void*,int,int) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 intptr_t JMP_32_SIZE ; 
 int MEM_COMMIT ; 
 int MEM_RESERVE ; 
 int /*<<< orphan*/  PAGE_EXECUTE_READWRITE ; 
 void* VirtualAlloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int VirtualQueryEx (int /*<<< orphan*/ ,void const*,TYPE_2__*,int) ; 

__attribute__((used)) static void setup_64bit_bounce(struct func_hook *hook, intptr_t *offset)
{
	MEMORY_BASIC_INFORMATION mbi;
	uintptr_t address;
	uintptr_t newdiff;
	SYSTEM_INFO si;
	bool success;
	int pagesize;
	int i;

	success = VirtualQueryEx(GetCurrentProcess(),
				 (const void *)hook->func_addr, &mbi,
				 sizeof(mbi));
	if (!success)
		return;

	GetSystemInfo(&si);
	pagesize = (int)si.dwAllocationGranularity;

	address = (uintptr_t)mbi.AllocationBase - pagesize;
	for (i = 0; i < 256; i++, address -= pagesize) {
		hook->bounce_addr = VirtualAlloc((LPVOID)address, pagesize,
						 MEM_RESERVE | MEM_COMMIT,
						 PAGE_EXECUTE_READWRITE);
		if (hook->bounce_addr)
			break;
	}

	if (!hook->bounce_addr) {
		address = (uintptr_t)mbi.AllocationBase + mbi.RegionSize +
			  pagesize;
		for (i = 0; i < 256; i++, address += pagesize) {
			hook->bounce_addr =
				VirtualAlloc((LPVOID)address, pagesize,
					     MEM_RESERVE | MEM_COMMIT,
					     PAGE_EXECUTE_READWRITE);
			if (hook->bounce_addr)
				break;
		}
	}

	if (!hook->bounce_addr)
		return;

	if ((hook->func_addr + 5) > (uintptr_t)hook->bounce_addr)
		newdiff = hook->func_addr + 5 - (uintptr_t)hook->bounce_addr;
	else
		newdiff = (uintptr_t)hook->bounce_addr - hook->func_addr + 5;

	if (newdiff <= 0x7ffffff0) {
		uint8_t *addr = (uint8_t *)hook->bounce_addr;

		FillMemory(hook->bounce_addr, pagesize, 0xCC);

		*(addr++) = 0xFF;
		*(addr++) = 0x25;
		*((uint32_t *)addr) = 0;
		*((uint64_t *)(addr + 4)) = hook->hook_addr;

		hook->hook_addr = (uint64_t)hook->bounce_addr;
		*offset = hook->hook_addr - hook->func_addr - JMP_32_SIZE;
		hook->is_64bit_jump = false;
	}
}