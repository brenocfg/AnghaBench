#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int type; scalar_t__ cbData; int /*<<< orphan*/ * pbData; } ;
typedef  TYPE_1__* PKIWI_CREDENTIAL_KEY ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
#define  CREDENTIALS_KEY_TYPE_DPAPI_PROTECTION 131 
#define  CREDENTIALS_KEY_TYPE_NTLM 130 
#define  CREDENTIALS_KEY_TYPE_ROOTKEY 129 
#define  CREDENTIALS_KEY_TYPE_SHA1 128 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_oe_credential_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

VOID kuhl_m_sekurlsa_genericKeyOutput(PKIWI_CREDENTIAL_KEY key, LPCWSTR sid)
{
	if(key && key->cbData)
	{
		switch(key->type)
		{
		case CREDENTIALS_KEY_TYPE_NTLM:
			kprintf(L"\n\t * NTLM     : ");
			if(sid)
				kuhl_m_dpapi_oe_credential_add(sid, NULL, key->pbData, NULL, NULL, NULL);
			break;
		case CREDENTIALS_KEY_TYPE_SHA1:
			kprintf(L"\n\t * SHA1     : ");
			if(sid)
				kuhl_m_dpapi_oe_credential_add(sid, NULL, NULL, key->pbData, NULL, NULL);
			break;
		case CREDENTIALS_KEY_TYPE_ROOTKEY:
			kprintf(L"\n\t * RootKey  : ");
			break;
		case CREDENTIALS_KEY_TYPE_DPAPI_PROTECTION:
			kprintf(L"\n\t * DPAPI    : ");
			if(sid)
				kuhl_m_dpapi_oe_credential_add(sid, NULL, NULL, NULL, key->pbData, NULL);
			break;
		default:
			kprintf(L"\n\t * %08x : ", key->type);
		}
		kull_m_string_wprintf_hex(key->pbData, key->cbData, 0);
	}
}