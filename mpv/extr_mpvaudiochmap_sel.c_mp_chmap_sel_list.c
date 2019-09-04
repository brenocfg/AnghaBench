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
 int /*<<< orphan*/  mp_chmap_sel_fallback (struct mp_chmap_sel*,struct mp_chmap*) ; 

void mp_chmap_sel_list(struct mp_chmap *c, struct mp_chmap *maps, int num_maps)
{
    // This is a separate function to keep messing with mp_chmap_sel internals
    // within this source file.
    struct mp_chmap_sel sel = {
        .chmaps = maps,
        .num_chmaps = num_maps,
    };
    mp_chmap_sel_fallback(&sel, c);
}