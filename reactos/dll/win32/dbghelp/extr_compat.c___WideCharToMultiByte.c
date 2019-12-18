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
typedef  int /*<<< orphan*/  UINT ;
typedef  int* LPSTR ;
typedef  int* LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int strlenW (int*) ; 

INT
__WideCharToMultiByte(UINT page, DWORD flags, LPCWSTR src, INT srclen,
                                LPSTR dst, INT dstlen, LPCSTR defchar, BOOL *used )
{
    int i;

    if (!src || !srclen || (!dst && dstlen))
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        return 0;
    }

    if (srclen < 0) srclen = strlenW(src) + 1;
    
    if(!dstlen)
        return srclen;
    
    for(i=0; i<srclen && i<dstlen; i++)
        dst[i] = src[i] & 0xFF;

    if (used) *used = FALSE;
    
    return i;
}