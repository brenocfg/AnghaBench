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
struct TYPE_5__ {int valCount; TYPE_1__* pAVal; } ;
struct TYPE_4__ {int /*<<< orphan*/  valLen; int /*<<< orphan*/ * pVal; } ;
typedef  int /*<<< orphan*/  SCHEMA_PREFIX_TABLE ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ ATTRVALBLOCK ;
typedef  int /*<<< orphan*/  ATTRBLOCK ;

/* Variables and functions */
 TYPE_2__* kull_m_rpc_drsr_findAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PVOID kull_m_rpc_drsr_findMonoAttr(SCHEMA_PREFIX_TABLE *prefixTable, ATTRBLOCK *attributes, LPCSTR szOid, PVOID data, DWORD *size)
{
	PVOID ptr = NULL;
	ATTRVALBLOCK *valblock;

	if(data)
		*(PVOID *)data = NULL;
	if(size)
		*size = 0;
	
	if(valblock = kull_m_rpc_drsr_findAttr(prefixTable, attributes, szOid))
	{
		if(valblock->valCount == 1)
		{
			ptr = valblock->pAVal[0].pVal;
			if(data)
				*(PVOID *)data = ptr;
			if(size)
				*size = valblock->pAVal[0].valLen;
		}
	}
	return ptr;
}