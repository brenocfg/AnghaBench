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
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 scalar_t__ CryptDuplicateKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CryptEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL kull_m_crypto_dh_simpleEncrypt(HCRYPTKEY key, LPVOID data, DWORD dataLen, LPVOID *out, DWORD *outLen)
{
	BOOL status = FALSE;
	HCRYPTKEY hTmp;
	*out = NULL;
	*outLen = dataLen;
	if(CryptDuplicateKey(key, NULL, 0, &hTmp))
	{
		if(CryptEncrypt(hTmp, 0, TRUE, 0, NULL, outLen, 0))
		{
			if(*out = LocalAlloc(LPTR, *outLen))
			{
				RtlCopyMemory(*out, data, dataLen);
				if(!(status = CryptEncrypt(hTmp, 0, TRUE, 0, (PBYTE) *out, &dataLen, *outLen)))
					*out = LocalFree(*out);
			}
		}
		CryptDestroyKey(hTmp);
	}
	return status;
}