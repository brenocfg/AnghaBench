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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  LDAP ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LDAP_AUTH_NEGOTIATE ; 
 void* LDAP_OPT_ON ; 
 int /*<<< orphan*/  LDAP_OPT_PROTOCOL_VERSION ; 
 int /*<<< orphan*/  LDAP_OPT_SIGN ; 
 int /*<<< orphan*/  LDAP_VERSION3 ; 
 int /*<<< orphan*/  ldap_bind_s (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldap_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldap_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ldap_set_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ldap_unbind (int /*<<< orphan*/ *) ; 

ULONG kuhl_m_lsadump_dcshadow_init_ldap(PWSTR szFQDN, LDAP** pld)
{
	DWORD dwErr = 0;
	LDAP* ld;
	if(ld = ldap_init(szFQDN, 389))
	{
		ULONG version = LDAP_VERSION3;
		// Set the version to 3.0 (default is 2.0).
		ldap_set_option(ld,LDAP_OPT_PROTOCOL_VERSION,(void*) &version);
		// enable LDAP signing - survive policies "network security: LDAP client signing requirements" + "domain controller: LDAP server signing requirements"
		ldap_set_option(ld,LDAP_OPT_SIGN,LDAP_OPT_ON);
		// ready to be enabled:
		//ldap_set_option(ld,LDAP_OPT_ENCRYPT,LDAP_OPT_ON);

		if(!(dwErr = ldap_connect(ld, NULL)))
		{
			if(!(dwErr = ldap_bind_s(ld, NULL, NULL, LDAP_AUTH_NEGOTIATE)))
			{
				*pld = ld;
			}
			else ldap_unbind(ld);
		}
		else ldap_unbind(ld);
	}
	return dwErr;
}