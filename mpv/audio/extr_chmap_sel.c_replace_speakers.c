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
struct mp_chmap {scalar_t__ num; scalar_t__* speaker; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mp_chmap_is_valid (struct mp_chmap*) ; 

__attribute__((used)) static bool replace_speakers(struct mp_chmap *map, struct mp_chmap list[2])
{
    assert(list[0].num == list[1].num);
    if (!mp_chmap_is_valid(map))
        return false;
    for (int dir = 0; dir < 2; dir++) {
        int from = dir ? 0 : 1;
        int to   = dir ? 1 : 0;
        bool replaced = false;
        struct mp_chmap t = *map;
        for (int n = 0; n < t.num; n++) {
            for (int i = 0; i < list[0].num; i++) {
                if (t.speaker[n] == list[from].speaker[i]) {
                    t.speaker[n] = list[to].speaker[i];
                    replaced = true;
                    break;
                }
            }
        }
        if (replaced && mp_chmap_is_valid(&t)) {
            *map = t;
            return true;
        }
    }
    return false;
}