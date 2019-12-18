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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  USHORT ;

/* Variables and functions */
 int /*<<< orphan*/  RtlUshortByteSwap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void PROFILE_ByteSwapShortBuffer(WCHAR * buffer, int len)
{
    int i;
    USHORT * shortbuffer = buffer;
    for (i = 0; i < len; i++)
        shortbuffer[i] = RtlUshortByteSwap(shortbuffer[i]);
}