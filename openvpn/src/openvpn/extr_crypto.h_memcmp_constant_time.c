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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline int
memcmp_constant_time(const void *a, const void *b, size_t size)
{
    const uint8_t *a1 = a;
    const uint8_t *b1 = b;
    int ret = 0;
    size_t i;

    for (i = 0; i < size; i++)
    {
        ret |= *a1++ ^ *b1++;
    }

    return ret;
}