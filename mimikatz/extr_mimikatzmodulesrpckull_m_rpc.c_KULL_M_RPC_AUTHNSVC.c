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
typedef  char* LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
#define  RPC_C_AUTHN_GSS_KERBEROS 131 
#define  RPC_C_AUTHN_GSS_NEGOTIATE 130 
#define  RPC_C_AUTHN_NONE 129 
#define  RPC_C_AUTHN_WINNT 128 

LPCWSTR KULL_M_RPC_AUTHNSVC(DWORD AuthnSvc)
{
	LPCWSTR szAuthnSvc;
	switch(AuthnSvc)
	{
	case RPC_C_AUTHN_NONE:
		szAuthnSvc = L"NONE";
		break;
	case RPC_C_AUTHN_GSS_NEGOTIATE:
		szAuthnSvc = L"GSS_NEGOTIATE";
		break;
	case RPC_C_AUTHN_WINNT:
		szAuthnSvc = L"WINNT";
		break;
	case RPC_C_AUTHN_GSS_KERBEROS:
		szAuthnSvc = L"GSS_KERBEROS";
		break;
	default:
		szAuthnSvc = L"?";
	}
	return szAuthnSvc;
}