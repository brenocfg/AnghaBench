#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  size_t ULONG ;
struct TYPE_12__ {TYPE_2__** HashBuckets; } ;
struct TYPE_11__ {scalar_t__ off2; scalar_t__ off3; scalar_t__ off1; } ;
struct TYPE_8__ {scalar_t__ Flink; } ;
struct TYPE_10__ {TYPE_1__ CallbackList; } ;
struct TYPE_9__ {scalar_t__ Object; struct TYPE_9__* ChainLink; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  TYPE_2__* POBJECT_DIRECTORY_ENTRY ;
typedef  TYPE_3__* POBJECT_CALLBACK_ENTRY ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ KiwiOsIndex ; 
 scalar_t__ KiwiOsIndex_VISTA ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 size_t OBJECT_HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  ObjectReferences ; 
 TYPE_7__** ObpTypeDirectoryObject ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kkll_m_modules_fromAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kkll_m_notify_desc_object_callback (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kkll_m_notify_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__**) ; 
 int /*<<< orphan*/  kprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_4__* pObpTypeDirectoryObjectOffsets ; 
 scalar_t__* procCallToName ; 

NTSTATUS kkll_m_notify_list_object(PKIWI_BUFFER outBuffer)
{
	NTSTATUS status = STATUS_SUCCESS;
	POBJECT_DIRECTORY_ENTRY pEntry;
	ULONG_PTR pType;
	POBJECT_CALLBACK_ENTRY pCallbackEntry;
	ULONG i, j;
	PVOID miniProc;

	if(!ObpTypeDirectoryObject)
		status = kkll_m_notify_search(ObjectReferences, ARRAYSIZE(ObjectReferences), (PUCHAR *) &ObpTypeDirectoryObject, NULL, &pObpTypeDirectoryObjectOffsets);
	
	if(ObpTypeDirectoryObject)
	{
		for(i = 0; NT_SUCCESS(status) && (i < OBJECT_HASH_TABLE_SIZE); i++)
		{
			for(pEntry = (*ObpTypeDirectoryObject)->HashBuckets[i]; NT_SUCCESS(status) && pEntry; pEntry = pEntry->ChainLink)
			{
				if(pType = (ULONG_PTR) pEntry->Object)
				{
					status = kprintf(outBuffer, L"\n * %wZ\n", pType + pObpTypeDirectoryObjectOffsets->off1);
					if(KiwiOsIndex >= KiwiOsIndex_VISTA)
					{
						for(pCallbackEntry = *(POBJECT_CALLBACK_ENTRY *) (pType + pObpTypeDirectoryObjectOffsets->off3) ; NT_SUCCESS(status) && (pCallbackEntry != (POBJECT_CALLBACK_ENTRY) (pType + pObpTypeDirectoryObjectOffsets->off3)) ; pCallbackEntry = (POBJECT_CALLBACK_ENTRY) pCallbackEntry->CallbackList.Flink)
							status = kkll_m_notify_desc_object_callback(pCallbackEntry, outBuffer);
					}
					for(j = 0; NT_SUCCESS(status) && (j < 8) ; j++)
					{
						if(miniProc = *(PVOID *) (pType + pObpTypeDirectoryObjectOffsets->off2 + (sizeof(PVOID) * j)))
						{
							status = kprintf(outBuffer, L"\t%s - ", procCallToName[j]);
							if(NT_SUCCESS(status))
								status = kkll_m_modules_fromAddr(outBuffer, miniProc);
						}
					}
				}
			}
		}
	}
	return status;
}