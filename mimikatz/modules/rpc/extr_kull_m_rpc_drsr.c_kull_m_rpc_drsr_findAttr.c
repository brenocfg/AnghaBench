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
struct TYPE_5__ {scalar_t__ attrTyp; int /*<<< orphan*/  AttrVal; } ;
struct TYPE_4__ {size_t attrCount; TYPE_2__* pAttr; } ;
typedef  int /*<<< orphan*/  SCHEMA_PREFIX_TABLE ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  ATTRVALBLOCK ;
typedef  scalar_t__ ATTRTYP ;
typedef  TYPE_1__ ATTRBLOCK ;
typedef  TYPE_2__ ATTR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_rpc_drsr_MakeAttid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

ATTRVALBLOCK * kull_m_rpc_drsr_findAttr(SCHEMA_PREFIX_TABLE *prefixTable, ATTRBLOCK *attributes, LPCSTR szOid)
{
	ATTRVALBLOCK *ptr = NULL;
	DWORD i;
	ATTR *attribut;
	ATTRTYP type;
	if(kull_m_rpc_drsr_MakeAttid(prefixTable, szOid, &type, FALSE))
	{
		for(i = 0; i < attributes->attrCount; i++)
		{
			attribut = &attributes->pAttr[i];
			if(attribut->attrTyp == type)
			{
				ptr = &attribut->AttrVal;
				break;
			}
		}
	}
	else PRINT_ERROR(L"Unable to get an ATTRTYP for %S\n", szOid);
	return ptr;
}