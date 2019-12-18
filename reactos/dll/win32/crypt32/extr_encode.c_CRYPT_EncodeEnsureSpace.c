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
struct TYPE_3__ {int /*<<< orphan*/ * (* pfnAlloc ) (int) ;} ;
typedef  int DWORD ;
typedef  TYPE_1__ CRYPT_ENCODE_PARA ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CRYPT_ENCODE_ALLOC_FLAG ; 
 int /*<<< orphan*/  ERROR_MORE_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * stub1 (int) ; 

BOOL CRYPT_EncodeEnsureSpace(DWORD dwFlags, const CRYPT_ENCODE_PARA *pEncodePara,
 BYTE *pbEncoded, DWORD *pcbEncoded, DWORD bytesNeeded)
{
    BOOL ret = TRUE;

    if (dwFlags & CRYPT_ENCODE_ALLOC_FLAG)
    {
        if (pEncodePara && pEncodePara->pfnAlloc)
            *(BYTE **)pbEncoded = pEncodePara->pfnAlloc(bytesNeeded);
        else
            *(BYTE **)pbEncoded = LocalAlloc(0, bytesNeeded);
        if (!*(BYTE **)pbEncoded)
            ret = FALSE;
        else
            *pcbEncoded = bytesNeeded;
    }
    else if (bytesNeeded > *pcbEncoded)
    {
        *pcbEncoded = bytesNeeded;
        SetLastError(ERROR_MORE_DATA);
        ret = FALSE;
    }
    else
        *pcbEncoded = bytesNeeded;
    return ret;
}