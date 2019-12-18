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

/* Variables and functions */

__attribute__((used)) static float color_to_float(DWORD color, DWORD size, DWORD offset)
{
    DWORD mask = size < 32 ? (1u << size) - 1 : ~0u;

    if (!size)
        return 1.0f;

    color >>= offset;
    color &= mask;

    return (float)color / (float)mask;
}