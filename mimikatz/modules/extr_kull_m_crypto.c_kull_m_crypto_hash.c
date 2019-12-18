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
struct TYPE_3__ {int /*<<< orphan*/  (* Finish ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Finalize ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Sum ) (int /*<<< orphan*/ ,int,scalar_t__) ;int /*<<< orphan*/  (* Initialize ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PKERB_CHECKSUM ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/  LPCBYTE ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTHASH ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  ALG_ID ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_CRC32 ; 
 int /*<<< orphan*/  CDLocateCheckSum (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  CRYPT_VERIFYCONTEXT ; 
 scalar_t__ CryptAcquireContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptCreateHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptDestroyHash (int /*<<< orphan*/ ) ; 
 scalar_t__ CryptGetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptHashData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 int /*<<< orphan*/  KERB_CHECKSUM_REAL_CRC32 ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_RSA_AES ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 

BOOL kull_m_crypto_hash(ALG_ID algid, LPCVOID data, DWORD dataLen, LPVOID hash, DWORD hashWanted)
{
	BOOL status = FALSE;
	HCRYPTPROV hProv;
	HCRYPTHASH hHash;
	DWORD hashLen;
	PBYTE buffer;
	PKERB_CHECKSUM pCheckSum;
	PVOID Context;

	if(algid == CALG_CRC32)
	{
		if((hashWanted == sizeof(DWORD)) && NT_SUCCESS(CDLocateCheckSum(KERB_CHECKSUM_REAL_CRC32, &pCheckSum)))
		{
			if(NT_SUCCESS(pCheckSum->Initialize(0, &Context)))
			{
				pCheckSum->Sum(Context, dataLen, data);
				status = NT_SUCCESS(pCheckSum->Finalize(Context, hash));
				pCheckSum->Finish(&Context);
			}
		}
	}
	else if(CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		if(CryptCreateHash(hProv, algid, 0, 0, &hHash))
		{
			if(CryptHashData(hHash, (LPCBYTE) data, dataLen, 0))
			{
				if(CryptGetHashParam(hHash, HP_HASHVAL, NULL, &hashLen, 0))
				{
					if(buffer = (PBYTE) LocalAlloc(LPTR, hashLen))
					{
						status = CryptGetHashParam(hHash, HP_HASHVAL, buffer, &hashLen, 0);
						RtlCopyMemory(hash, buffer, min(hashLen, hashWanted));
						LocalFree(buffer);
					}
				}
			}
			CryptDestroyHash(hHash);
		}
		CryptReleaseContext(hProv, 0);
	}
	return status;
}