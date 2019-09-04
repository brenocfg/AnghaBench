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
typedef  int BYTE ;

/* Variables and functions */

__attribute__((used)) static short fetch_short(const BYTE** ptr)
{
    short       ret;

    if (*(*ptr) & 1)
    {
        ret = (*(const unsigned short*)(*ptr) - 0x8000) / 2;
        (*ptr) += 2;
    }
    else
    {
        ret = (*(const unsigned char*)(*ptr) - 0x80) / 2;
        (*ptr)++;
    }
    return ret;
}