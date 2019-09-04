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
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static size_t last_blocks_correction_nist(const unsigned char *in,
                                          unsigned char *out, size_t len)
{
    size_t tail;

    if ((tail = len % 16) == 0)
        tail = 16;
    len -= 16 + tail;
    memcpy(out, in, len);
    /* flip two last blocks */
    memcpy(out + len, in + len + 16, tail);
    memcpy(out + len + tail, in + len, 16);
    len += 16 + tail;
    tail = 16;

    return tail;
}