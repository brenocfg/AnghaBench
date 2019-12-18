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
typedef  int /*<<< orphan*/  opad ;
typedef  int /*<<< orphan*/  ipad ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/ * LPCVOID ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_SHA1 ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  RtlFillMemory (int /*<<< orphan*/ *,int,char) ; 
 int SHA_DIGEST_LENGTH ; 
 scalar_t__ kull_m_crypto_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

BOOL kull_m_dpapi_hmac_sha1_incorrect(LPCVOID key, DWORD keyLen, LPCVOID salt, DWORD saltLen, LPCVOID entropy, DWORD entropyLen, LPCVOID data, DWORD dataLen, LPVOID outKey)
{
	BOOL status = FALSE;
	BYTE ipad[64], opad[64], hash[SHA_DIGEST_LENGTH], *bufferI, *bufferO;
	DWORD i;

	RtlFillMemory(ipad, sizeof(ipad), '6');
	RtlFillMemory(opad, sizeof(opad), '\\');
	for(i = 0; i < keyLen; i++)
	{
		ipad[i] ^= ((PBYTE) key)[i];
		opad[i] ^= ((PBYTE) key)[i];
	}
	if(bufferI = (PBYTE) LocalAlloc(LPTR, sizeof(ipad) + saltLen))
	{
		RtlCopyMemory(bufferI, ipad, sizeof(ipad));
		RtlCopyMemory(bufferI + sizeof(ipad), salt, saltLen);
		if(kull_m_crypto_hash(CALG_SHA1, bufferI, sizeof(ipad) + saltLen, hash, SHA_DIGEST_LENGTH))
		{
			if(bufferO = (PBYTE) LocalAlloc(LPTR, sizeof(opad) + SHA_DIGEST_LENGTH + entropyLen + dataLen))
			{
				RtlCopyMemory(bufferO, opad, sizeof(opad));
				RtlCopyMemory(bufferO + sizeof(opad), hash, SHA_DIGEST_LENGTH);
				if(entropy && entropyLen)
					RtlCopyMemory(bufferO + sizeof(opad) + SHA_DIGEST_LENGTH, entropy, entropyLen);
				if(data && dataLen)
					RtlCopyMemory(bufferO + sizeof(opad) + SHA_DIGEST_LENGTH + entropyLen, data, dataLen);
				
				status = kull_m_crypto_hash(CALG_SHA1, bufferO, sizeof(opad) + SHA_DIGEST_LENGTH + entropyLen + dataLen, outKey, SHA_DIGEST_LENGTH);
				LocalFree(bufferO);
			}
		}
		LocalFree(bufferI);
	}
	return status;
}