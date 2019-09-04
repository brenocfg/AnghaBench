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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 scalar_t__ likely (int) ; 

void *memcpy(void *dst, const void *src, size_t n) {
    if (likely(!(((uintptr_t)dst) & 3) && !(((uintptr_t)src) & 3))) {
        // pointers aligned
        uint32_t *d = dst;
        const uint32_t *s = src;

        // copy words first
        for (size_t i = (n >> 2); i; i--) {
            *d++ = *s++;
        }

        if (n & 2) {
            // copy half-word
            *(uint16_t*)d = *(const uint16_t*)s;
            d = (uint32_t*)((uint16_t*)d + 1);
            s = (const uint32_t*)((const uint16_t*)s + 1);
        }

        if (n & 1) {
            // copy byte
            *((uint8_t*)d) = *((const uint8_t*)s);
        }
    } else {
        // unaligned access, copy bytes
        uint8_t *d = dst;
        const uint8_t *s = src;

        for (; n; n--) {
            *d++ = *s++;
        }
    }

    return dst;
}