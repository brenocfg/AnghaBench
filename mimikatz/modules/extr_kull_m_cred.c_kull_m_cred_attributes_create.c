#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dwKeyword; int ValueSize; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PKULL_M_CRED_ATTRIBUTE ;
typedef  int PBYTE ;
typedef  int /*<<< orphan*/  KULL_M_CRED_ATTRIBUTE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 TYPE_1__* kull_m_cred_attribute_create (int) ; 
 int /*<<< orphan*/  kull_m_cred_attributes_delete (TYPE_1__**,int) ; 

BOOL kull_m_cred_attributes_create(PVOID data, PKULL_M_CRED_ATTRIBUTE **Attributes, DWORD count)
{
	BOOL status = FALSE;
	DWORD i, j;
	
	if((*Attributes) = (PKULL_M_CRED_ATTRIBUTE *) LocalAlloc(LPTR, count * sizeof(PKULL_M_CRED_ATTRIBUTE)))
	{
		for(i = 0, j = 0, status = TRUE; (i < count) && status; i++)
		{
			if((*Attributes)[i] = kull_m_cred_attribute_create((PBYTE) data + j))
				j +=  sizeof(KULL_M_CRED_ATTRIBUTE) - 2 * sizeof(PVOID) + (*Attributes)[i]->dwKeyword + (*Attributes)[i]->ValueSize;
			else status = FALSE;
		}
	}
	if(!status)
	{
		kull_m_cred_attributes_delete(*Attributes, count);
		*Attributes = NULL;
	}
	return status;
}