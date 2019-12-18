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
typedef  int int32_t ;

/* Variables and functions */
 int AMF3_INTEGER_MAX ; 

int
AMF3ReadInteger(const char *data, int32_t *valp)
{
    int i = 0;
    int32_t val = 0;

    while (i <= 2)
    {
        /* handle first 3 bytes */
        if (data[i] & 0x80)
        {
            /* byte used */
            val <<= 7;		/* shift up */
            val |= (data[i] & 0x7f);	/* add bits */
            i++;
        }
        else
        {
            break;
        }
    }

    if (i > 2)
    {
        /* use 4th byte, all 8bits */
        val <<= 8;
        val |= data[3];

        /* range check */
        if (val > AMF3_INTEGER_MAX)
            val -= (1 << 29);
    }
    else
    {
        /* use 7bits of last unparsed byte (0xxxxxxx) */
        val <<= 7;
        val |= data[i];
    }

    *valp = val;

    return i > 2 ? 4 : i + 1;
}