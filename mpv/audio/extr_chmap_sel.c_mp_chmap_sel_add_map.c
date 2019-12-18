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
struct mp_chmap_sel {scalar_t__ num_chmaps; struct mp_chmap* chmaps; int /*<<< orphan*/  tmp; struct mp_chmap* chmaps_storage; } ;
struct mp_chmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ MP_ARRAY_SIZE (struct mp_chmap*) ; 
 int /*<<< orphan*/  MP_TARRAY_GROW (int /*<<< orphan*/ ,struct mp_chmap*,scalar_t__) ; 
 int /*<<< orphan*/  mp_chmap_is_valid (struct mp_chmap const*) ; 
 struct mp_chmap* talloc_memdup (int /*<<< orphan*/ ,struct mp_chmap*,int) ; 

void mp_chmap_sel_add_map(struct mp_chmap_sel *s, const struct mp_chmap *map)
{
    if (!mp_chmap_is_valid(map))
        return;
    if (!s->chmaps)
        s->chmaps = s->chmaps_storage;
    if (s->num_chmaps == MP_ARRAY_SIZE(s->chmaps_storage)) {
        if (!s->tmp)
            return;
        s->chmaps = talloc_memdup(s->tmp, s->chmaps, sizeof(s->chmaps_storage));
    }
    if (s->chmaps != s->chmaps_storage)
        MP_TARRAY_GROW(s->tmp, s->chmaps, s->num_chmaps);
    s->chmaps[s->num_chmaps++] = *map;
}