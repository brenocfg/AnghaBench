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
typedef  size_t UINT ;
typedef  size_t LPWSTR ;
typedef  int /*<<< orphan*/  LONGLONG ;
typedef  size_t INT ;

/* Variables and functions */
 size_t FormatInteger (int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  IDS_BYTES_FORMAT ; 
 size_t LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  StringCchCopyExW (size_t,size_t,char*,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInst ; 

UINT
FormatByteSize(LONGLONG cbSize, LPWSTR pwszResult, UINT cchResultMax)
{
    INT cchWritten;
    LPWSTR pwszEnd;
    size_t cchRemaining;

    /* Write formated bytes count */
    cchWritten = FormatInteger(cbSize, pwszResult, cchResultMax);
    if (!cchWritten)
        return 0;

    /* Copy " bytes" to buffer */
    pwszEnd = pwszResult + cchWritten;
    cchRemaining = cchResultMax - cchWritten;
    StringCchCopyExW(pwszEnd, cchRemaining, L" ", &pwszEnd, &cchRemaining, 0);
    cchWritten = LoadStringW(hInst, IDS_BYTES_FORMAT, pwszEnd, cchRemaining);
    cchRemaining -= cchWritten;

    return cchResultMax - cchRemaining;
}