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
typedef  int USHORT ;
typedef  int ULONG ;
typedef  int BYTE ;

/* Variables and functions */

__attribute__((used)) static ULONG fetch_ulong(const BYTE** ptr)
{
    ULONG        ret;

    if (*(*ptr) & 1)
    {
        ret = *(const ULONG*)(*ptr) / 2;
        (*ptr) += 4;
    }
    else
    {
        ret = *(const USHORT*)(*ptr) / 2;
        (*ptr) += 2;
    }
    return ret;
}