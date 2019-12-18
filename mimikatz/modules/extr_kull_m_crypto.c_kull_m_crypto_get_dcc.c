#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int Length; int MaximumLength; int /*<<< orphan*/ * Buffer; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  int PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ LSA_UNICODE_STRING ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_SHA1 ; 
 int /*<<< orphan*/  FALSE ; 
 int LM_NTLM_HASH_LENGTH ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (int,int,int) ; 
 int /*<<< orphan*/  RtlDigestNTLM (TYPE_1__*,int) ; 
 int /*<<< orphan*/  RtlDowncaseUnicodeString (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ kull_m_crypto_pkcs5_pbkdf2_hmac (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

NTSTATUS kull_m_crypto_get_dcc(PBYTE dcc, PBYTE ntlm, PUNICODE_STRING Username, DWORD realIterations)
{
	NTSTATUS status;
	LSA_UNICODE_STRING HashAndLowerUsername;
	LSA_UNICODE_STRING LowerUsername;
	BYTE buffer[LM_NTLM_HASH_LENGTH];

	status = RtlDowncaseUnicodeString(&LowerUsername, Username, TRUE);
	if(NT_SUCCESS(status))
	{
		HashAndLowerUsername.Length = HashAndLowerUsername.MaximumLength = LowerUsername.Length + LM_NTLM_HASH_LENGTH;
		if(HashAndLowerUsername.Buffer = (PWSTR) LocalAlloc(LPTR, HashAndLowerUsername.MaximumLength))
		{
			RtlCopyMemory(HashAndLowerUsername.Buffer, ntlm, LM_NTLM_HASH_LENGTH);
			RtlCopyMemory((PBYTE) HashAndLowerUsername.Buffer + LM_NTLM_HASH_LENGTH, LowerUsername.Buffer, LowerUsername.Length);
			status = RtlDigestNTLM(&HashAndLowerUsername, dcc);
			if(realIterations && NT_SUCCESS(status))
			{
				if(kull_m_crypto_pkcs5_pbkdf2_hmac(CALG_SHA1, dcc, LM_NTLM_HASH_LENGTH, LowerUsername.Buffer, LowerUsername.Length, realIterations, buffer, LM_NTLM_HASH_LENGTH, FALSE))
				{
					RtlCopyMemory(dcc, buffer, LM_NTLM_HASH_LENGTH);
					status = STATUS_SUCCESS;
				}
			}
			LocalFree(HashAndLowerUsername.Buffer);
		}
		RtlFreeUnicodeString(&LowerUsername);
	}
	return status;
}