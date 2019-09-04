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

__attribute__((used)) static void ctr64_inc(unsigned char *counter)
{
    int n = 8;
    unsigned char c;

    do {
        --n;
        c = counter[n];
        ++c;
        counter[n] = c;
        if (c)
            return;
    } while (n);
}