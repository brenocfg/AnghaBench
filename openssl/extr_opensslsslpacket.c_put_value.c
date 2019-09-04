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

__attribute__((used)) static int put_value(unsigned char *data, size_t value, size_t len)
{
    for (data += len - 1; len > 0; len--) {
        *data = (unsigned char)(value & 0xff);
        data--;
        value >>= 8;
    }

    /* Check whether we could fit the value in the assigned number of bytes */
    if (value > 0)
        return 0;

    return 1;
}