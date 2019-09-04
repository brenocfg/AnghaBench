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
struct mp_chmap_sel {int dummy; } ;
struct mp_chmap {int dummy; } ;

/* Variables and functions */
 int MP_NUM_CHANNELS ; 
 int /*<<< orphan*/  mp_chmap_from_channels (struct mp_chmap*,int) ; 
 int /*<<< orphan*/  mp_chmap_sel_add_map (struct mp_chmap_sel*,struct mp_chmap*) ; 

void mp_chmap_sel_add_waveext_def(struct mp_chmap_sel *s)
{
    for (int n = 1; n <= MP_NUM_CHANNELS; n++) {
        struct mp_chmap map;
        mp_chmap_from_channels(&map, n);
        mp_chmap_sel_add_map(s, &map);
    }
}