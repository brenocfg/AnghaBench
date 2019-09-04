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
#define  SAM_ALIAS_OBJECT 137 
#define  SAM_APP_BASIC_GROUP 136 
#define  SAM_APP_QUERY_GROUP 135 
#define  SAM_DOMAIN_OBJECT 134 
#define  SAM_GROUP_OBJECT 133 
#define  SAM_MACHINE_ACCOUNT 132 
#define  SAM_NON_SECURITY_ALIAS_OBJECT 131 
#define  SAM_NON_SECURITY_GROUP_OBJECT 130 
#define  SAM_TRUST_ACCOUNT 129 
#define  SAM_USER_OBJECT 128 

LPCWSTR kuhl_m_lsadump_samAccountType_toString(DWORD accountType)
{
	LPCWSTR target;
	switch(accountType)
	{
	case SAM_DOMAIN_OBJECT:
		target = L"DOMAIN_OBJECT";
		break;
	case SAM_GROUP_OBJECT:
		target = L"GROUP_OBJECT";
		break;
	case SAM_NON_SECURITY_GROUP_OBJECT:
		target = L"NON_SECURITY_GROUP_OBJECT";
		break;
	case SAM_ALIAS_OBJECT:
		target = L"ALIAS_OBJECT";
		break;
	case SAM_NON_SECURITY_ALIAS_OBJECT:
		target = L"NON_SECURITY_ALIAS_OBJECT";
		break;
	case SAM_USER_OBJECT:
		target = L"USER_OBJECT";
		break;
	case SAM_MACHINE_ACCOUNT:
		target = L"MACHINE_ACCOUNT";
		break;
	case SAM_TRUST_ACCOUNT:
		target = L"TRUST_ACCOUNT";
		break;
	case SAM_APP_BASIC_GROUP:
		target = L"APP_BASIC_GROUP";
		break;
	case SAM_APP_QUERY_GROUP:
		target = L"APP_QUERY_GROUP";
		break;
	default:
		target = L"unknown";
	}
	return target;
}