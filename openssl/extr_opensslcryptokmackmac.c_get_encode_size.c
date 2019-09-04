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

__attribute__((used)) static unsigned int get_encode_size(size_t bits)
{
    unsigned int cnt = 0, sz = sizeof(size_t);

    while (bits && (cnt < sz)) {
        ++cnt;
        bits >>= 8;
    }
    /* If bits is zero 1 byte is required */
    if (cnt == 0)
        cnt = 1;
    return cnt;
}