#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_12__ {int /*<<< orphan*/ * member_1; TYPE_2__* member_0; } ;
struct TYPE_11__ {int /*<<< orphan*/  address; } ;
struct TYPE_9__ {int /*<<< orphan*/  RightChild; } ;
struct TYPE_10__ {TYPE_1__ BalancedRoot; } ;
typedef  TYPE_2__ RTL_AVL_TABLE ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  PLUID ;
typedef  TYPE_3__* PKULL_M_MEMORY_ADDRESS ;
typedef  TYPE_4__ KULL_M_MEMORY_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  KULL_M_MEMORY_GLOBAL_OWN_HANDLE ; 
 int /*<<< orphan*/ * kuhl_m_sekurlsa_utils_pFromAVLByLuidRec (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_memory_copy (TYPE_4__*,TYPE_3__*,int) ; 

PVOID kuhl_m_sekurlsa_utils_pFromAVLByLuid(PKULL_M_MEMORY_ADDRESS pTable, ULONG LUIDoffset, PLUID luidToFind)
{
	PVOID resultat = NULL;
	RTL_AVL_TABLE maTable;
	KULL_M_MEMORY_ADDRESS data = {&maTable, &KULL_M_MEMORY_GLOBAL_OWN_HANDLE};

	if(kull_m_memory_copy(&data, pTable, sizeof(RTL_AVL_TABLE)))
	{
		pTable->address = maTable.BalancedRoot.RightChild;
		resultat = kuhl_m_sekurlsa_utils_pFromAVLByLuidRec(pTable, LUIDoffset, luidToFind);
	}
	return resultat;
}