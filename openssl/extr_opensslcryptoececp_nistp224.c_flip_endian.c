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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */

__attribute__((used)) static void flip_endian(u8 *out, const u8 *in, unsigned len)
{
    unsigned i;
    for (i = 0; i < len; ++i)
        out[i] = in[len - 1 - i];
}