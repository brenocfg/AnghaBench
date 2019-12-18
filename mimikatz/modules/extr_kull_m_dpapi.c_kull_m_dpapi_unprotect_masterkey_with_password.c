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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  sha2 ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  PKULL_M_DPAPI_MASTERKEY ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;
typedef  scalar_t__ ALG_ID ;

/* Variables and functions */
 scalar_t__ CALG_MD4 ; 
 scalar_t__ CALG_SHA1 ; 
 int /*<<< orphan*/  CALG_SHA_256 ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_crypto_hash (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int kull_m_crypto_hash_len (scalar_t__) ; 
 scalar_t__ kull_m_crypto_pkcs5_pbkdf2_hmac (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__ kull_m_dpapi_unprotect_masterkey_with_userHash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ ) ; 

BOOL kull_m_dpapi_unprotect_masterkey_with_password(DWORD flags, PKULL_M_DPAPI_MASTERKEY masterkey, PCWSTR password, PCWSTR sid, BOOL isKeyOfProtectedUser, PVOID *output, DWORD *outputLen)
{
	BOOL status = FALSE;
	ALG_ID PassAlg;
	DWORD PassLen, SidLen = (DWORD) wcslen(sid) * sizeof(wchar_t);
	PVOID PassHash;
	BYTE sha2[32];
	
	PassAlg = (flags & 4) ? CALG_SHA1 : CALG_MD4;
	PassLen = kull_m_crypto_hash_len(PassAlg);
	if(PassHash = LocalAlloc(LPTR, PassLen))
	{
		if(kull_m_crypto_hash(PassAlg, password, (DWORD) wcslen(password) * sizeof(wchar_t), PassHash, PassLen))
		{
			if(isKeyOfProtectedUser && (PassAlg == CALG_MD4))
				if(kull_m_crypto_pkcs5_pbkdf2_hmac(CALG_SHA_256, PassHash, PassLen, sid, SidLen, 10000, sha2, sizeof(sha2), FALSE))
					kull_m_crypto_pkcs5_pbkdf2_hmac(CALG_SHA_256, sha2, sizeof(sha2), sid, SidLen, 1, (PBYTE) PassHash, PassLen, FALSE);

			status = kull_m_dpapi_unprotect_masterkey_with_userHash(masterkey, PassHash, PassLen, sid, output, outputLen);
		}
		LocalFree(PassHash);
	}
	return status;
}