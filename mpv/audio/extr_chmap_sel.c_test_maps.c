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
struct mp_chmap_sel {int num_chmaps; struct mp_chmap* chmaps; } ;
struct mp_chmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ mp_chmap_equals_reordered (struct mp_chmap*,struct mp_chmap*) ; 

__attribute__((used)) static bool test_maps(const struct mp_chmap_sel *s, struct mp_chmap *map)
{
    for (int n = 0; n < s->num_chmaps; n++) {
        if (mp_chmap_equals_reordered(&s->chmaps[n], map)) {
            *map = s->chmaps[n];
            return true;
        }
    }
    return false;
}