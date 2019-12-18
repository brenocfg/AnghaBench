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

/* Variables and functions */

char *
AMF_EncodeInt16(char *output, char *outend, short nVal)
{
    if (output+2 > outend)
        return NULL;

    output[1] = nVal & 0xff;
    output[0] = nVal >> 8;
    return output+2;
}