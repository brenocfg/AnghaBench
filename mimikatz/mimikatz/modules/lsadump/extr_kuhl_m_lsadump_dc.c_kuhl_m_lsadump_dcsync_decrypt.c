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
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int LM_NTLM_HASH_LENGTH ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  RtlDecryptDES2blocks1DWORD (scalar_t__,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

BOOL kuhl_m_lsadump_dcsync_decrypt(PBYTE encodedData, DWORD encodedDataSize, DWORD rid, LPCWSTR prefix, BOOL isHistory)
{
	DWORD i;
	BOOL status = FALSE;
	BYTE data[LM_NTLM_HASH_LENGTH];
	for(i = 0; i < encodedDataSize; i += LM_NTLM_HASH_LENGTH)
	{
		status = NT_SUCCESS(RtlDecryptDES2blocks1DWORD(encodedData + i, &rid, data));
		if(status)
		{
			if(isHistory)
				kprintf(L"    %s-%2u: ", prefix, i / LM_NTLM_HASH_LENGTH);
			else
				kprintf(L"  Hash %s: ", prefix);
			kull_m_string_wprintf_hex(data, LM_NTLM_HASH_LENGTH, 0);
			kprintf(L"\n");
		}
		else PRINT_ERROR(L"RtlDecryptDES2blocks1DWORD");
	}
	return status;
}