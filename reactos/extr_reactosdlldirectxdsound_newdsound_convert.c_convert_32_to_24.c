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
typedef  int UINT ;
typedef  scalar_t__ INT ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int le32 (int const) ; 
 int /*<<< orphan*/  src_advance (void const**,int,scalar_t__*,int*,int) ; 

__attribute__((used)) static void convert_32_to_24 (const void *src, void *dst, UINT src_stride,
        UINT dst_stride, INT count, UINT freqAcc, UINT adj)
{
    while (count > 0)
    {
        DWORD dest = le32(*(const DWORD *)src);
        BYTE *dest24 = dst;

        dest24[0] = dest / 256;
        dest24[1] = dest / 65536;
        dest24[2] = dest / 16777216;

        dst = (char *)dst + dst_stride;
        src_advance(&src, src_stride, &count, &freqAcc, adj);
    }
}