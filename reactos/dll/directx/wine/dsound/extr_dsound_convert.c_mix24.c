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
typedef  int /*<<< orphan*/  INT ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void mix24(BYTE *src, INT *dst, unsigned len)
{
    TRACE("%p - %p %d\n", src, dst, len);
    len /= 3;
    while (len--)
    {
        DWORD field;
        field = ((DWORD)src[2] << 16) + ((DWORD)src[1] << 8) + (DWORD)src[0];
        if (src[2] & 0x80)
            field |= 0xFF000000U;
        *(dst++) += field;
        ++src;
    }
}