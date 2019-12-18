#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {scalar_t__ RightChild; } ;
struct TYPE_5__ {TYPE_1__ BalancedRoot; } ;
typedef  TYPE_2__ RTL_AVL_TABLE ;
typedef  int /*<<< orphan*/  PLUID ;

/* Variables and functions */
 scalar_t__ ReadMemory (scalar_t__,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ kuhl_m_sekurlsa_utils_pFromAVLByLuidRec (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ULONG_PTR kuhl_m_sekurlsa_utils_pFromAVLByLuid(ULONG_PTR pTable, ULONG LUIDoffset, PLUID luidToFind)
{
	ULONG_PTR resultat = 0;
	RTL_AVL_TABLE maTable;
	if(ReadMemory(pTable, &maTable, sizeof(RTL_AVL_TABLE), NULL))
	{
		pTable = (ULONG_PTR) maTable.BalancedRoot.RightChild;
		resultat = kuhl_m_sekurlsa_utils_pFromAVLByLuidRec(pTable, LUIDoffset, luidToFind);
	}
	return resultat;
}