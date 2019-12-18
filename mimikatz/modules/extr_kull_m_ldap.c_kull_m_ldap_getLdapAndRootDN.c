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
typedef  scalar_t__ PWCHAR ;
typedef  int /*<<< orphan*/  PLDAP ;
typedef  scalar_t__ PCWCHAR ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LDAP_AUTH_NEGOTIATE ; 
 int /*<<< orphan*/  LDAP_PORT ; 
 scalar_t__ LDAP_SUCCESS ; 
 scalar_t__ LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 scalar_t__ kull_m_ldap_getRootDomainNamingContext (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ldap_bind_s (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldap_init (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldap_unbind (int /*<<< orphan*/ ) ; 

BOOL kull_m_ldap_getLdapAndRootDN(PCWCHAR system, PCWCHAR nc, PLDAP *ld, PWCHAR *rootDn)
{
	BOOL status = FALSE;
	DWORD dwErr;

	if(*ld = ldap_init((PWCHAR) system, LDAP_PORT))
	{
		if(*rootDn = kull_m_ldap_getRootDomainNamingContext(nc, *ld))
		{
			dwErr = ldap_bind_s(*ld, NULL, NULL, LDAP_AUTH_NEGOTIATE);
			status = (dwErr == LDAP_SUCCESS);
			if(!status)
			{
				PRINT_ERROR(L"ldap_bind_s 0x%x (%u)\n", dwErr, dwErr);
				*rootDn = (PWCHAR) LocalFree(*rootDn);
			}
		}
		if(!status)
			ldap_unbind(*ld);
	}
	else PRINT_ERROR(L"ldap_init\n");
	return status;
}