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
 int /*<<< orphan*/  AMF_BOOLEAN ; 

char *
AMF_EncodeBoolean(char *output, char *outend, int bVal)
{
    if (output+2 > outend)
        return NULL;

    *output++ = AMF_BOOLEAN;

    *output++ = bVal ? 0x01 : 0x00;

    return output;
}