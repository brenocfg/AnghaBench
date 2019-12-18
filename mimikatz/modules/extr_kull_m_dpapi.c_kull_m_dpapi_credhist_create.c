#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t dwNextLen; } ;
struct TYPE_11__ {int __dwCount; TYPE_3__** entries; TYPE_1__ current; } ;
struct TYPE_9__ {size_t dwNextLen; } ;
struct TYPE_10__ {TYPE_2__ header; } ;
typedef  TYPE_3__* PKULL_M_DPAPI_CREDHIST_ENTRY ;
typedef  TYPE_4__* PKULL_M_DPAPI_CREDHIST ;
typedef  size_t PBYTE ;
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/  KULL_M_DPAPI_CREDHIST_HEADER ;
typedef  int /*<<< orphan*/  KULL_M_DPAPI_CREDHIST ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_4__*,size_t,int) ; 
 TYPE_3__* kull_m_dpapi_credhist_entry_create (size_t,size_t) ; 

PKULL_M_DPAPI_CREDHIST kull_m_dpapi_credhist_create(LPCVOID data, DWORD size)
{
	PKULL_M_DPAPI_CREDHIST credhist = NULL;
	DWORD currSize, sumSize, i;
	if(data && (credhist = (PKULL_M_DPAPI_CREDHIST) LocalAlloc(LPTR, sizeof(KULL_M_DPAPI_CREDHIST))))
	{
		RtlCopyMemory(credhist, (PBYTE) data + size - sizeof(KULL_M_DPAPI_CREDHIST_HEADER), sizeof(KULL_M_DPAPI_CREDHIST_HEADER));

		for(
			sumSize = sizeof(KULL_M_DPAPI_CREDHIST_HEADER), currSize = credhist->current.dwNextLen;
			(sumSize < size) && currSize;
		currSize = ((PKULL_M_DPAPI_CREDHIST_ENTRY) ((PBYTE) data + size - (sumSize + currSize)))->header.dwNextLen, sumSize += currSize, credhist->__dwCount++
			);

		if(credhist->entries = (PKULL_M_DPAPI_CREDHIST_ENTRY *) LocalAlloc(LPTR, credhist->__dwCount * sizeof(PKULL_M_DPAPI_CREDHIST_ENTRY)))
			for(
				i = 0, sumSize = sizeof(KULL_M_DPAPI_CREDHIST_HEADER), currSize = credhist->current.dwNextLen;
				(sumSize < size) && currSize;
		currSize = ((PKULL_M_DPAPI_CREDHIST_ENTRY) ((PBYTE) data + size - (sumSize + currSize)))->header.dwNextLen, sumSize += currSize, i++
			)
			credhist->entries[i] = kull_m_dpapi_credhist_entry_create(((PBYTE) data + size - (sumSize + currSize)), currSize);
	}
	return credhist;
}