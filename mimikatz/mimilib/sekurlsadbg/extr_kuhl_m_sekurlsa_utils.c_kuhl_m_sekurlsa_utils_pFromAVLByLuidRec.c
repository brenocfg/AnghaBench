#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_7__ {scalar_t__ RightChild; scalar_t__ LeftChild; } ;
struct TYPE_8__ {TYPE_1__ BalancedRoot; scalar_t__ OrderedPointer; } ;
typedef  TYPE_2__ RTL_AVL_TABLE ;
typedef  TYPE_2__* PVOID ;
typedef  int /*<<< orphan*/  PLUID ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  LUID ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 TYPE_2__* LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (TYPE_2__*) ; 
 scalar_t__ ReadMemory (scalar_t__,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ SecEqualLuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ULONG_PTR kuhl_m_sekurlsa_utils_pFromAVLByLuidRec(ULONG_PTR pTable, ULONG LUIDoffset, PLUID luidToFind)
{
	ULONG_PTR resultat = 0;
	PVOID buffer;
	RTL_AVL_TABLE maTable;

	if(ReadMemory(pTable, &maTable, sizeof(RTL_AVL_TABLE), NULL))
	{
		if(pTable = (ULONG_PTR) maTable.OrderedPointer)
		{
			if(buffer = LocalAlloc(LPTR, LUIDoffset + sizeof(LUID)))
			{
				if(ReadMemory(pTable, buffer, LUIDoffset + sizeof(LUID), NULL))
				{
					if(SecEqualLuid(luidToFind, (PLUID) ((PBYTE) buffer + LUIDoffset)))
						resultat = (ULONG_PTR) maTable.OrderedPointer;
				}
				LocalFree(buffer);
			}
		}
		if(!resultat && (pTable = (ULONG_PTR) maTable.BalancedRoot.LeftChild))
			resultat = kuhl_m_sekurlsa_utils_pFromAVLByLuidRec(pTable, LUIDoffset, luidToFind);
		if(!resultat && (pTable = (ULONG_PTR) maTable.BalancedRoot.RightChild))
			resultat = kuhl_m_sekurlsa_utils_pFromAVLByLuidRec(pTable, LUIDoffset, luidToFind);
	}
	return resultat;
}