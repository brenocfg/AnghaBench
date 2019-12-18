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
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;
typedef  int /*<<< orphan*/  ALG_ID ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RtlFillMemory (int /*<<< orphan*/ *,int,char) ; 
 int kull_m_crypto_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ min (scalar_t__,int) ; 

BOOL kull_m_crypto_DeriveKeyRaw(ALG_ID hashId, LPVOID hash, DWORD hashLen, LPVOID key, DWORD keyLen)
{
	BOOL status = FALSE;
	BYTE buffer[152], ipad[64], opad[64];
	DWORD i;
	
	if(status = (hashLen >= keyLen))
		RtlCopyMemory(key, hash, keyLen);
	else
	{
		RtlFillMemory(ipad, sizeof(ipad), '6');
		RtlFillMemory(opad, sizeof(opad), '\\');
		for(i = 0; i < hashLen; i++)
		{
			ipad[i] ^= ((PBYTE) hash)[i];
			opad[i] ^= ((PBYTE) hash)[i];
		}
		if(kull_m_crypto_hash(hashId, ipad, sizeof(ipad), buffer, hashLen))
			if(status = kull_m_crypto_hash(hashId, opad, sizeof(opad), buffer + hashLen, hashLen))
				RtlCopyMemory(key, buffer, min(keyLen, 2 * hashLen));
	}
	return status;
}