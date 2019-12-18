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
typedef  int uint32_t ;
struct window_data {scalar_t__ relaxed; scalar_t__ excess_free; scalar_t__ evicted; scalar_t__ dirty; scalar_t__ age; } ;

/* Variables and functions */

__attribute__((used)) static void window_sum(struct window_data *wd, struct window_data *w,
        uint32_t size) {
    for (int x = 0; x < size; x++) {
        struct window_data *d = &wd[x];
        w->age += d->age;
        w->dirty += d->dirty;
        w->evicted += d->evicted;
        w->excess_free += d->excess_free;
        w->relaxed += d->relaxed;
    }
}