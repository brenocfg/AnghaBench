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
struct window_global {scalar_t__ pool_low; scalar_t__ pool_high; } ;

/* Variables and functions */

__attribute__((used)) static void window_global_sum(struct window_global *wg,
        struct window_global *w, uint32_t size) {
    for (int x = 0; x < size; x++) {
        struct window_global *d = &wg[x];
        w->pool_high += d->pool_high;
        w->pool_low += d->pool_low;
    }
}