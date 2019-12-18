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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ Base64HeaderToBinaryW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Base64ToBinaryW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DecodeBinaryToBinaryW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_DATA ; 

__attribute__((used)) static LONG DecodeAnyW(LPCWSTR pszString, DWORD cchString,
 BYTE *pbBinary, DWORD *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags)
{
    LONG ret;

    ret = Base64HeaderToBinaryW(pszString, cchString, pbBinary, pcbBinary,
     pdwSkip, pdwFlags);
    if (ret == ERROR_INVALID_DATA)
        ret = Base64ToBinaryW(pszString, cchString, pbBinary, pcbBinary,
         pdwSkip, pdwFlags);
    if (ret == ERROR_INVALID_DATA)
        ret = DecodeBinaryToBinaryW(pszString, cchString, pbBinary, pcbBinary,
         pdwSkip, pdwFlags);
    return ret;
}