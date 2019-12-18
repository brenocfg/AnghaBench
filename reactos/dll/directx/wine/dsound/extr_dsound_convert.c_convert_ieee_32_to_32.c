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
typedef  float INT32 ;
typedef  scalar_t__ INT ;
typedef  float DWORD ;

/* Variables and functions */
 float le32 (float) ; 
 int /*<<< orphan*/  src_advance (void const**,int,scalar_t__*,int*,int) ; 

__attribute__((used)) static void convert_ieee_32_to_32 (const void *src, void *dst, UINT src_stride,
        UINT dst_stride, INT count, UINT freqAcc, UINT adj)
{
    while (count > 0)
    {
        DWORD src_le = le32(*(DWORD *) src);
        float v = *((float *) &src_le);
        INT32 *d = (INT32 *) dst;

        if (v < -1.0f)
            *d = -2147483647 - 1; /* silence warning */
        else if (v >  1.0f)
            *d = 2147483647;
        else
            *d = v * 2147483647.5f - 0.5f;

        *d = le32(*d);

        dst = (char *)dst + dst_stride;
        src_advance(&src, src_stride, &count, &freqAcc, adj);
    }
}