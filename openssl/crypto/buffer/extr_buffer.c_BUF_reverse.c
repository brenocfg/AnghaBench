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

void BUF_reverse(unsigned char *out, const unsigned char *in, size_t size)
{
    size_t i;
    if (in) {
        out += size - 1;
        for (i = 0; i < size; i++)
            *out-- = *in++;
    } else {
        unsigned char *q;
        char c;
        q = out + size - 1;
        for (i = 0; i < size / 2; i++) {
            c = *q;
            *q-- = *out;
            *out++ = c;
        }
    }
}