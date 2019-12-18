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
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

void mp_seq_multiply(const void *items, size_t item_sz, size_t len, size_t times, void *dest) {
    for (size_t i = 0; i < times; i++) {
        size_t copy_sz = item_sz * len;
        memcpy(dest, items, copy_sz);
        dest = (char*)dest + copy_sz;
    }
}