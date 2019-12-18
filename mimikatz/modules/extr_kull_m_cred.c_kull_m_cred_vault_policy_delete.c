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
struct TYPE_4__ {scalar_t__ key; struct TYPE_4__* Name; } ;
typedef  TYPE_1__* PKULL_M_CRED_VAULT_POLICY ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 int /*<<< orphan*/  kull_m_cred_vault_policy_key_delete (scalar_t__) ; 

void kull_m_cred_vault_policy_delete(PKULL_M_CRED_VAULT_POLICY policy)
{
	if(policy)
	{
		if(policy->Name)
			LocalFree(policy->Name);
		if(policy->key)
			kull_m_cred_vault_policy_key_delete(policy->key);
		LocalFree(policy);
	}
}