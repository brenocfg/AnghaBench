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
struct mp_chmap_sel {int /*<<< orphan*/ * speakers; } ;
struct mp_chmap {int num; size_t* speaker; } ;

/* Variables and functions */

__attribute__((used)) static bool test_speakers(const struct mp_chmap_sel *s, struct mp_chmap *map)
{
    for (int n = 0; n < map->num; n++) {
        if (!s->speakers[map->speaker[n]])
            return false;
    }
    return true;
}