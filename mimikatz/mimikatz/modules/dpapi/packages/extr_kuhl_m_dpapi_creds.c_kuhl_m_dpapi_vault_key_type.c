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
struct TYPE_3__ {int id; scalar_t__ IV; scalar_t__ szIV; } ;
typedef  TYPE_1__* PKULL_M_CRED_VAULT_CREDENTIAL_ATTRIBUTE ;
typedef  int /*<<< orphan*/ * LPCVOID ;
typedef  scalar_t__ LPCBYTE ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AES_128_KEY_SIZE ; 
 int /*<<< orphan*/  AES_256_KEY_SIZE ; 
 int /*<<< orphan*/  CALG_AES_128 ; 
 int /*<<< orphan*/  CALG_AES_256 ; 
 int /*<<< orphan*/  CRYPT_MODE_CBC ; 
 int /*<<< orphan*/  CryptSetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  KP_IV ; 
 int /*<<< orphan*/  KP_MODE ; 
 int kull_m_crypto_hkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL kuhl_m_dpapi_vault_key_type(PKULL_M_CRED_VAULT_CREDENTIAL_ATTRIBUTE attribute, HCRYPTPROV hProv, BYTE aes128[AES_128_KEY_SIZE], BYTE aes256[AES_256_KEY_SIZE], HCRYPTKEY *hKey, BOOL *isAttr)
{
	BOOL status = FALSE;
	DWORD mode = CRYPT_MODE_CBC, calgId, keyLen;
	LPCVOID key;

	*isAttr = attribute->id && (attribute->id < 100);
	if(*isAttr)
	{
		calgId = CALG_AES_128;
		key = aes128;
		keyLen = AES_128_KEY_SIZE;
		
	}
	else
	{
		calgId = CALG_AES_256;
		key = aes256;
		keyLen = AES_256_KEY_SIZE;
	}

	if(status = kull_m_crypto_hkey(hProv, calgId, key, keyLen, 0, hKey, NULL))
	{
		CryptSetKeyParam(*hKey, KP_MODE, (LPCBYTE) &mode, 0);
		if(attribute->szIV && attribute->IV)
			CryptSetKeyParam(*hKey, KP_IV, attribute->IV, 0);
	}
	return status;
}