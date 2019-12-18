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
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CryptSetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KP_IV ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ kull_m_crypto_aesBlockEncryptDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

BOOL kull_m_crypto_aesCTSEncrypt(HCRYPTKEY hKey, PBYTE data, DWORD szData, PBYTE pbIV)
{
	BOOL status = FALSE;
	DWORD nbBlock, lastLen;
	BYTE buffer[32], *ptr;
	
	if(szData > 16)
	{
		if(CryptSetKeyParam(hKey, KP_IV, pbIV, 0))
		{
			nbBlock = (szData + 15) >> 4;
			lastLen = (szData & 0xf) ? (szData & 0xf) : 16;
			if (nbBlock <= 2 || kull_m_crypto_aesBlockEncryptDecrypt(hKey, data, nbBlock - 2, TRUE))
			{
				ptr = &data[16 * (nbBlock - 2)];
				RtlCopyMemory(buffer, ptr, lastLen + 16);
				RtlZeroMemory(&buffer[lastLen + 16], 16 - lastLen);
				if(status = kull_m_crypto_aesBlockEncryptDecrypt(hKey, buffer, 2, TRUE))
				{
					RtlCopyMemory(ptr, buffer + 16, 16);
					RtlCopyMemory(&data[16 * nbBlock - 16], buffer, lastLen);
				}
			}
		}
	}
	else if(szData == 16)
		status = kull_m_crypto_aesBlockEncryptDecrypt(hKey, data, 1, TRUE);
	
	return status;
}