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

__attribute__((used)) static void ctr64_add(unsigned char *counter, size_t inc)
{
    size_t n = 8, val = 0;

    counter += 8;
    do {
        --n;
        val += counter[n] + (inc & 0xff);
        counter[n] = (unsigned char)val;
        val >>= 8;              /* carry bit */
        inc >>= 8;
    } while (n && (inc || val));
}