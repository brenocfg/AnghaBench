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

__attribute__((used)) static void swap_copy(unsigned char *out, const void *in, size_t len)
{
    size_t j;

    for (j = 0; j < len; j++)
        out[j] = ((unsigned char *)in)[len - j - 1];
}