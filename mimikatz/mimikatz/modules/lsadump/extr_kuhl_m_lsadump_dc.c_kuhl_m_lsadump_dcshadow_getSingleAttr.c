#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int bv_len; scalar_t__ bv_val; } ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  int /*<<< orphan*/  PLDAPMessage ;
typedef  int /*<<< orphan*/  PLDAP ;
typedef  scalar_t__ PCWCHAR ;
typedef  scalar_t__ PCHAR ;
typedef  TYPE_1__* PBERVAL ;
typedef  int /*<<< orphan*/  BERVAL ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ LocalFree (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,int) ; 
 int ldap_count_values_len (TYPE_1__**) ; 
 TYPE_1__** ldap_get_values_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldap_value_free_len (TYPE_1__**) ; 

PBERVAL kuhl_m_lsadump_dcshadow_getSingleAttr(PLDAP ld, PLDAPMessage pMessage, PCWCHAR attr)
{
	PBERVAL *tmp, result = NULL;
	if(tmp = ldap_get_values_len(ld, pMessage, (PWCHAR) attr))
	{
		if(ldap_count_values_len(tmp) == 1)
		{
			if(result = (PBERVAL) LocalAlloc(LPTR, sizeof(BERVAL)))
			{
				result->bv_len = tmp[0]->bv_len;
				if(result->bv_val = (PCHAR) LocalAlloc(LPTR, result->bv_len))
					RtlCopyMemory(result->bv_val, tmp[0]->bv_val, result->bv_len);
				else result = (PBERVAL) LocalFree(result);
			}
		}
		ldap_value_free_len(tmp);
	}
	return result;
}