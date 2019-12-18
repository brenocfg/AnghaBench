#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_9__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_10__ {int /*<<< orphan*/  Buffer; } ;
typedef  int /*<<< orphan*/ * PCWCHAR ;
typedef  TYPE_2__ OEM_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_MD5 ; 
 int /*<<< orphan*/  CALG_SHA1 ; 
 int /*<<< orphan*/  CALG_SHA_256 ; 
 int LM_NTLM_HASH_LENGTH ; 
 int MD5_DIGEST_LENGTH ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlDigestLM (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlDigestNTLM (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlFreeOemString (TYPE_2__*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlUpcaseUnicodeStringToOemString (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  kull_m_crypto_get_dcc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ kull_m_crypto_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int wcstoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_crypto_hash(int argc, wchar_t * argv[])
{
	PCWCHAR szCount, szPassword = NULL, szUsername = NULL;
	UNICODE_STRING uPassword, uUsername;/*, uTmp;
	ANSI_STRING aTmp;*/
	OEM_STRING oTmp;
	DWORD count = 10240;
	BYTE hash[LM_NTLM_HASH_LENGTH], dcc[LM_NTLM_HASH_LENGTH], md5[MD5_DIGEST_LENGTH], sha1[SHA_DIGEST_LENGTH], sha2[32];
	
	kull_m_string_args_byName(argc, argv, L"password", &szPassword, NULL);
	kull_m_string_args_byName(argc, argv, L"user", &szUsername, NULL);
	if(kull_m_string_args_byName(argc, argv, L"count", &szCount, NULL))
		count = wcstoul(szCount, NULL, 0);

	RtlInitUnicodeString(&uPassword, szPassword);
	RtlInitUnicodeString(&uUsername, szUsername);
	if(NT_SUCCESS(RtlDigestNTLM(&uPassword, hash)))
	{
		kprintf(L"NTLM: "); kull_m_string_wprintf_hex(hash, LM_NTLM_HASH_LENGTH, 0); kprintf(L"\n");
		if(szUsername)
		{
			if(NT_SUCCESS(kull_m_crypto_get_dcc(dcc, hash, &uUsername, 0)))
			{
				kprintf(L"DCC1: "); kull_m_string_wprintf_hex(dcc, LM_NTLM_HASH_LENGTH, 0); kprintf(L"\n");
				if(NT_SUCCESS(kull_m_crypto_get_dcc(dcc, hash, &uUsername, count)))
				{
					kprintf(L"DCC2: "); kull_m_string_wprintf_hex(dcc, LM_NTLM_HASH_LENGTH, 0); kprintf(L"\n");
				}
			}
		}
	}

	//if(NT_SUCCESS(RtlUpcaseUnicodeString(&uTmp, &uPassword, TRUE)))
	//{
	//	if(NT_SUCCESS(RtlUnicodeStringToAnsiString(&aTmp, &uTmp, TRUE)))
	//	{
	//		if(NT_SUCCESS(RtlDigestLM(aTmp.Buffer, hash)))
	//		{
	//			kprintf(L"LM  : "); kull_m_string_wprintf_hex(hash, LM_NTLM_HASH_LENGTH, 0); kprintf(L"\n");
	//		}
	//		RtlFreeAnsiString(&aTmp);
	//	}
	//	RtlFreeUnicodeString(&uTmp);
	//}

	if(NT_SUCCESS(RtlUpcaseUnicodeStringToOemString(&oTmp, &uPassword, TRUE)))
	{
		if(NT_SUCCESS(RtlDigestLM(oTmp.Buffer, hash)))
		{
			kprintf(L"LM  : "); kull_m_string_wprintf_hex(hash, LM_NTLM_HASH_LENGTH, 0); kprintf(L"\n");
		}
		RtlFreeOemString(&oTmp);
	}

	if(kull_m_crypto_hash(CALG_MD5, uPassword.Buffer, uPassword.Length, md5, MD5_DIGEST_LENGTH))
		kprintf(L"MD5 : "); kull_m_string_wprintf_hex(md5, MD5_DIGEST_LENGTH, 0); kprintf(L"\n");
	if(kull_m_crypto_hash(CALG_SHA1, uPassword.Buffer, uPassword.Length, sha1, SHA_DIGEST_LENGTH))
		kprintf(L"SHA1: "); kull_m_string_wprintf_hex(sha1, SHA_DIGEST_LENGTH, 0); kprintf(L"\n");
	if(kull_m_crypto_hash(CALG_SHA_256, uPassword.Buffer, uPassword.Length, sha2, 32))
		kprintf(L"SHA2: "); kull_m_string_wprintf_hex(sha2, 32, 0); kprintf(L"\n");

	return STATUS_SUCCESS;
}