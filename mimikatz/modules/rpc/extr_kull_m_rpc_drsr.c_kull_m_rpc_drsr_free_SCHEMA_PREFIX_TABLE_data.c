#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_4__* elements; } ;
struct TYPE_7__ {TYPE_1__ prefix; } ;
struct TYPE_6__ {size_t PrefixCount; TYPE_4__* pPrefixEntry; } ;
typedef  TYPE_2__ SCHEMA_PREFIX_TABLE ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  MIDL_user_free (TYPE_4__*) ; 

void kull_m_rpc_drsr_free_SCHEMA_PREFIX_TABLE_data(SCHEMA_PREFIX_TABLE *prefixTable)
{
	DWORD i;
	if(prefixTable)
	{
		if(prefixTable->pPrefixEntry)
		{
			for(i = 0; i < prefixTable->PrefixCount; i++)
				if(prefixTable->pPrefixEntry[i].prefix.elements)
					MIDL_user_free(prefixTable->pPrefixEntry[i].prefix.elements);
			MIDL_user_free(prefixTable->pPrefixEntry);
		}
	}
}