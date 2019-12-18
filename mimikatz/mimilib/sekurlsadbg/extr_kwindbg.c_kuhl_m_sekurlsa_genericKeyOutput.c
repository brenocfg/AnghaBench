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
struct TYPE_3__ {int type; int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
typedef  TYPE_1__* PKIWI_CREDENTIAL_KEY ;

/* Variables and functions */
#define  CREDENTIALS_KEY_TYPE_DPAPI_PROTECTION 131 
#define  CREDENTIALS_KEY_TYPE_NTLM 130 
#define  CREDENTIALS_KEY_TYPE_ROOTKEY 129 
#define  CREDENTIALS_KEY_TYPE_SHA1 128 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_dprintf_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID kuhl_m_sekurlsa_genericKeyOutput(PKIWI_CREDENTIAL_KEY key)
{
	switch(key->type)
	{
	case CREDENTIALS_KEY_TYPE_NTLM:
		dprintf("\n\t * NTLM     : ");
		break;
	case CREDENTIALS_KEY_TYPE_SHA1:
		dprintf("\n\t * SHA1     : ");
		break;
	case CREDENTIALS_KEY_TYPE_ROOTKEY:
		dprintf("\n\t * RootKey  : ");
		break;
	case CREDENTIALS_KEY_TYPE_DPAPI_PROTECTION:
		dprintf("\n\t * DPAPI    : ");
		break;
	default:
		dprintf("\n\t * %08x : ", key->type);
	}
	kull_m_string_dprintf_hex(key->pbData, key->cbData, 0);
}