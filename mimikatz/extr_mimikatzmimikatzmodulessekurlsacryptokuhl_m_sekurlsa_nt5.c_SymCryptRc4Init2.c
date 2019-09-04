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
struct TYPE_3__ {int* S; int i; scalar_t__ j; } ;
typedef  int SIZE_T ;
typedef  TYPE_1__* PSYMCRYPT_RC4_STATE ;
typedef  int* LPCBYTE ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */

BOOL SymCryptRc4Init2(PSYMCRYPT_RC4_STATE pState, LPCBYTE pbKey, SIZE_T cbKey)
{
	BOOL status = cbKey && (cbKey <= 256);
	SIZE_T i, j, keyIdx;
	BYTE T;

	if(status)
	{
		for(i = 0; i < 256; i++)
			pState->S[i] = (BYTE) i;
		j = 0;
		keyIdx = 0;
		for(i = 0; i < 256; i++)
		{
			T = pState->S[i];
			j = (j + T + pbKey[keyIdx]) & 0xff;
			pState->S[i] = pState->S[j];
			pState->S[j] = T;
			keyIdx++;
			if(keyIdx == cbKey)
				keyIdx = 0;
		}
		pState->i = 1;
		pState->j = 0;
	}
	return status;
}