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
struct mp_chmap {int num; int* speaker; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int MP_SPEAKER_ID_NA ; 

void mp_chmap_remove_na(struct mp_chmap *map)
{
    struct mp_chmap new = {0};
    for (int n = 0; n < map->num; n++) {
        int sp = map->speaker[n];
        if (sp != MP_SPEAKER_ID_NA)
            new.speaker[new.num++] = map->speaker[n];
    }
    *map = new;
}