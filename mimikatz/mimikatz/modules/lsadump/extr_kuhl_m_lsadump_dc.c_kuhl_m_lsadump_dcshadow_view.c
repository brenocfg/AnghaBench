#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t cNumObjects; TYPE_4__* pObjects; } ;
struct TYPE_10__ {size_t cbAttributes; TYPE_3__* pAttributes; int /*<<< orphan*/  szObjectDN; } ;
struct TYPE_8__ {scalar_t__ valCount; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pszValue; TYPE_2__ AttrVal; TYPE_1__* pAttribute; } ;
struct TYPE_7__ {int /*<<< orphan*/  szAttributeName; } ;
typedef  TYPE_5__* PDCSHADOW_PUSH_REQUEST ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 

NTSTATUS kuhl_m_lsadump_dcshadow_view(PDCSHADOW_PUSH_REQUEST request)
{
	DWORD i, j, k;
	for(i = 0; i < request->cNumObjects; i++)
	{
		kprintf(L"[%u] Object DN: %s\n", i, request->pObjects[i].szObjectDN);
		for(j = 0; j < request->pObjects[i].cbAttributes; j++)
		{
			kprintf(L"  [%u] Attribute: %s\n", j, request->pObjects[i].pAttributes[j].pAttribute->szAttributeName);
			if(request->pObjects[i].pAttributes[j].AttrVal.valCount == 0)
				kprintf(L"  Attribute is empty (existing value will be removed)\n");
			else for(k = 0; k < request->pObjects[i].pAttributes[j].AttrVal.valCount; k++)
					kprintf(L"    [%u] %s\n", k, request->pObjects[i].pAttributes[j].pszValue[k]);
		}
	}
	return STATUS_SUCCESS;
}