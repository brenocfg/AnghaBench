#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t NameCount; int /*<<< orphan*/ * Names; } ;
typedef  TYPE_1__* PKERB_EXTERNAL_NAME ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ LocalFree (TYPE_1__*) ; 
 int /*<<< orphan*/  kull_m_string_freeUnicodeStringBuffer (int /*<<< orphan*/ *) ; 

void kuhl_m_kerberos_ticket_freeExternalName(PKERB_EXTERNAL_NAME pName)
{
	DWORD i;
	if(pName)
	{
		for(i = 0; i < pName->NameCount; i++)
			kull_m_string_freeUnicodeStringBuffer(&pName->Names[i]);
		pName = (PKERB_EXTERNAL_NAME) LocalFree(pName);
	}
}