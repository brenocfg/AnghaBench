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
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  scalar_t__ PUCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ RtlEqualMemory (int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS kkll_m_memory_search(const PUCHAR adresseBase, const PUCHAR adresseMaxMin, const UCHAR *pattern, PUCHAR *addressePattern, SIZE_T longueur)
{
	for(*addressePattern = adresseBase; (adresseMaxMin > adresseBase) ? (*addressePattern <= adresseMaxMin) : (*addressePattern >= adresseMaxMin); *addressePattern += (adresseMaxMin > adresseBase) ? 1 : -1)
		if(RtlEqualMemory(pattern, *addressePattern, longueur))
			return STATUS_SUCCESS;
	*addressePattern = NULL;
	return STATUS_NOT_FOUND;
}