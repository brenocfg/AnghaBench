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
 scalar_t__ mp_chmap_diffn (struct mp_chmap*,struct mp_chmap*) ; 
 scalar_t__ mp_chmap_is_valid (struct mp_chmap*) ; 

__attribute__((used)) static void replace_submap(struct mp_chmap *dst, struct mp_chmap *a,
                           struct mp_chmap *b)
{
    struct mp_chmap t = *dst;
    if (!mp_chmap_is_valid(&t) || mp_chmap_diffn(a, &t) != 0)
        return;
    assert(a->num == b->num);
    for (int n = 0; n < t.num; n++) {
        for (int i = 0; i < a->num; i++) {
            if (t.speaker[n] == a->speaker[i]) {
                t.speaker[n] = b->speaker[i];
                break;
            }
        }
    }
    if (mp_chmap_is_valid(&t))
        *dst = t;
}