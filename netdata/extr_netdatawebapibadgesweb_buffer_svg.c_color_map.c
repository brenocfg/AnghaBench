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
typedef  scalar_t__ uint32_t ;
struct badge_color {char const* name; scalar_t__ hash; char const* color; } ;

/* Variables and functions */
 struct badge_color* badge_colors ; 
 void* simple_hash (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline const char *color_map(const char *color) {
    static int max = -1;
    int i;

    if(unlikely(max == -1)) {
        for(i = 0; badge_colors[i].name ;i++)
            badge_colors[i].hash = simple_hash(badge_colors[i].name);

        max = i;
    }

    uint32_t hash = simple_hash(color);

    for(i = 0; i < max; i++) {
        struct badge_color *ptr = &badge_colors[i];

        if(hash == ptr->hash && !strcmp(color, ptr->name))
            return ptr->color;
    }

    return color;
}