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
struct mp_chmap {int num; int /*<<< orphan*/ * speaker; } ;

/* Variables and functions */
 int MP_NUM_CHANNELS ; 
 int /*<<< orphan*/  MP_SPEAKER_ID_NA ; 
 int /*<<< orphan*/  assert (int) ; 

void mp_chmap_fill_na(struct mp_chmap *map, int num)
{
    assert(num <= MP_NUM_CHANNELS);
    while (map->num < num)
        map->speaker[map->num++] = MP_SPEAKER_ID_NA;
}