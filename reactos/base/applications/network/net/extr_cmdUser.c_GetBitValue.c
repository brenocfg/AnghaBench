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
typedef  int* PBYTE ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static
BOOL
GetBitValue(
    PBYTE pBitmap,
    DWORD dwBitNumber)
{
    DWORD dwIndex = dwBitNumber / 8;
    BYTE Mask = 1 << (dwBitNumber & 7);

    return ((pBitmap[dwIndex] & Mask) != 0);
}