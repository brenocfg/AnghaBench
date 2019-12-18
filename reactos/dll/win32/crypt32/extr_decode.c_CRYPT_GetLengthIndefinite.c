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
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CMSG_INDEFINITE_LENGTH ; 
 int /*<<< orphan*/  CRYPT_E_ASN1_CORRUPT ; 
 int /*<<< orphan*/  CRYPT_E_ASN1_EOD ; 
 int /*<<< orphan*/  CRYPT_E_ASN1_LARGE ; 
 int /*<<< orphan*/  FALSE ; 
 int GET_LEN_BYTES (int const) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL CRYPT_GetLengthIndefinite(const BYTE *pbEncoded, DWORD cbEncoded,
 DWORD *len)
{
    BOOL ret;

    if (cbEncoded <= 1)
    {
        SetLastError(CRYPT_E_ASN1_CORRUPT);
        ret = FALSE;
    }
    else if (pbEncoded[1] <= 0x7f)
    {
        if (pbEncoded[1] + 1 > cbEncoded)
        {
            SetLastError(CRYPT_E_ASN1_EOD);
            ret = FALSE;
        }
        else
        {
            *len = pbEncoded[1];
            ret = TRUE;
        }
    }
    else if (pbEncoded[1] == 0x80)
    {
        *len = CMSG_INDEFINITE_LENGTH;
        ret = TRUE;
    }
    else
    {
        BYTE lenLen = GET_LEN_BYTES(pbEncoded[1]);

        if (lenLen > sizeof(DWORD) + 1)
        {
            SetLastError(CRYPT_E_ASN1_LARGE);
            ret = FALSE;
        }
        else if (lenLen + 2 > cbEncoded)
        {
            SetLastError(CRYPT_E_ASN1_CORRUPT);
            ret = FALSE;
        }
        else
        {
            DWORD out = 0;

            pbEncoded += 2;
            while (--lenLen)
            {
                out <<= 8;
                out |= *pbEncoded++;
            }
            if (out + lenLen + 1 > cbEncoded)
            {
                SetLastError(CRYPT_E_ASN1_EOD);
                ret = FALSE;
            }
            else
            {
                *len = out;
                ret = TRUE;
            }
        }
    }
    return ret;
}