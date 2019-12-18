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
typedef  int PBYTE ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/ * LPCVOID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  scalar_t__ ALG_ID ;

/* Variables and functions */
 scalar_t__ CALG_SHA1 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int) ; 
 int /*<<< orphan*/  RtlCopyMemory (int,int /*<<< orphan*/ *,int) ; 
 int SHA_DIGEST_LENGTH ; 
 scalar_t__ kull_m_crypto_hash (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kull_m_crypto_hmac (scalar_t__,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kull_m_dpapi_hmac_sha1_incorrect (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

BOOL kull_m_dpapi_sessionkey(LPCVOID masterkey, DWORD masterkeyLen, LPCVOID salt, DWORD saltLen, LPCVOID entropy, DWORD entropyLen, LPCVOID data, DWORD dataLen, ALG_ID hashAlg, LPVOID outKey, DWORD outKeyLen)
{
	BOOL status = FALSE;
	LPCVOID pKey = NULL;
	BYTE dgstMasterKey[SHA_DIGEST_LENGTH];
	PBYTE tmp;
	if(masterkeyLen == SHA_DIGEST_LENGTH)
		pKey = masterkey;
	else if(kull_m_crypto_hash(CALG_SHA1, masterkey, masterkeyLen, dgstMasterKey, SHA_DIGEST_LENGTH))
		pKey = dgstMasterKey;
	
	if(pKey)
	{
		if((hashAlg == CALG_SHA1) && (entropy || data))
			status = kull_m_dpapi_hmac_sha1_incorrect(masterkey, masterkeyLen, salt, saltLen, entropy, entropyLen, data, dataLen, outKey);
		else if(tmp = (PBYTE) LocalAlloc(LPTR, saltLen + entropyLen + dataLen))
		{
			RtlCopyMemory(tmp, salt, saltLen);
			if(entropy && entropyLen)
				RtlCopyMemory(tmp + saltLen, entropy, entropyLen);
			if(data && dataLen)
				RtlCopyMemory(tmp + saltLen + entropyLen, data, dataLen);
			status = kull_m_crypto_hmac(hashAlg, pKey, SHA_DIGEST_LENGTH, tmp, saltLen + entropyLen + dataLen, outKey, outKeyLen);
			LocalFree(tmp);
		}
	}
	return status;
}