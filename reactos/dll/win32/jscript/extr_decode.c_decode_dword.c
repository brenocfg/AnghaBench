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
typedef  size_t WCHAR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t const ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int* digits ; 

__attribute__((used)) static BOOL decode_dword(const WCHAR *p, DWORD *ret)
{
    DWORD i;

    for(i=0; i<6; i++) {
        if(p[i] >= ARRAY_SIZE(digits) || digits[p[i]] == 0xff)
            return FALSE;
    }
    if(p[6] != '=' || p[7] != '=')
        return FALSE;

    *ret = (digits[p[0]] << 2)
        + (digits[p[1]] >> 4)
        + ((digits[p[1]] & 0xf) << 12)
        + ((digits[p[2]] >> 2) << 8)
        + ((digits[p[2]] & 0x3) << 22)
        + (digits[p[3]] << 16)
        + ((digits[p[4]] << 2) << 24)
        + ((digits[p[5]] >> 4) << 24);
    return TRUE;
}