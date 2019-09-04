#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* member_0; char* member_1; int member_2; int member_3; char const* match; } ;
typedef  TYPE_1__ rar_pattern_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static const rar_pattern_t *FindVolumePattern(const char *location)
{
    static const rar_pattern_t patterns[] = {
        { ".part1.rar",   "%s.part%.1d.rar", 2,   9 },
        { ".part01.rar",  "%s.part%.2d.rar", 2,  99, },
        { ".part001.rar", "%s.part%.3d.rar", 2, 999 },
        { ".rar",         "%s.%c%.2d",       0, 999 },
        { NULL, NULL, 0, 0 },
    };

    const size_t location_size = strlen(location);
    for (int i = 0; patterns[i].match != NULL; i++) {
        const size_t match_size = strlen(patterns[i].match);

        if (location_size < match_size)
            continue;
        if (!strcmp(&location[location_size - match_size], patterns[i].match))
            return &patterns[i];
    }
    return NULL;
}