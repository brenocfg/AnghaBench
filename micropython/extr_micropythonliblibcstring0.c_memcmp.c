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

int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *s1_8 = s1;
    const uint8_t *s2_8 = s2;
    while (n--) {
        char c1 = *s1_8++;
        char c2 = *s2_8++;
        if (c1 < c2) return -1;
        else if (c1 > c2) return 1;
    }
    return 0;
}