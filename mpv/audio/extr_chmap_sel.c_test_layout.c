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
struct mp_chmap_sel {scalar_t__ allow_any; } ;
struct mp_chmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_chmap_is_valid (struct mp_chmap*) ; 
 scalar_t__ test_maps (struct mp_chmap_sel const*,struct mp_chmap*) ; 
 scalar_t__ test_speakers (struct mp_chmap_sel const*,struct mp_chmap*) ; 
 scalar_t__ test_waveext (struct mp_chmap_sel const*,struct mp_chmap*) ; 

__attribute__((used)) static bool test_layout(const struct mp_chmap_sel *s, struct mp_chmap *map)
{
    if (!mp_chmap_is_valid(map))
        return false;

    return s->allow_any || test_waveext(s, map) || test_speakers(s, map) ||
           test_maps(s, map);
}