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
struct TYPE_5__ {size_t __count; struct TYPE_5__* Credentials; } ;
typedef  TYPE_1__* PKULL_M_CRED_LEGACY_CREDS_BLOB ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 int /*<<< orphan*/  kull_m_cred_legacy_cred_delete (TYPE_1__) ; 

void kull_m_cred_legacy_creds_delete(PKULL_M_CRED_LEGACY_CREDS_BLOB creds)
{
	DWORD i;
	if(creds)
	{
		if(creds->Credentials)
		{
			for(i = 0; i < creds->__count; i++)
				kull_m_cred_legacy_cred_delete(creds->Credentials[i]);
			LocalFree(creds->Credentials);
		}
		LocalFree(creds);
	}
}