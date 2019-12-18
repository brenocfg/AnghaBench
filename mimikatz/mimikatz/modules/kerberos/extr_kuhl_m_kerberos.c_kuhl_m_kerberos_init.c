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
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LsaConnectUntrusted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LsaLookupAuthenticationPackage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_AuthenticationPackageId_Kerberos ; 
 int /*<<< orphan*/  g_hLSA ; 
 scalar_t__ g_isAuthPackageKerberos ; 
 int /*<<< orphan*/  kerberosPackageName ; 

NTSTATUS kuhl_m_kerberos_init()
{
	NTSTATUS status = LsaConnectUntrusted(&g_hLSA);
	if(NT_SUCCESS(status))
	{
		status = LsaLookupAuthenticationPackage(g_hLSA, &kerberosPackageName, &g_AuthenticationPackageId_Kerberos);
		g_isAuthPackageKerberos = NT_SUCCESS(status);
	}
	return status;
}