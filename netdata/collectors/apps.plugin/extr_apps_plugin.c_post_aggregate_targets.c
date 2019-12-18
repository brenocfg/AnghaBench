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
struct target {scalar_t__ collected_starttime; scalar_t__ starttime; struct target* next; } ;

/* Variables and functions */

__attribute__((used)) static inline void post_aggregate_targets(struct target *root) {
    struct target *w;
    for (w = root; w ; w = w->next) {
        if(w->collected_starttime) {
            if (!w->starttime || w->collected_starttime < w->starttime) {
                w->starttime = w->collected_starttime;
            }
        } else {
            w->starttime = 0;
        }
    }
}