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

/* Variables and functions */
 int MP_ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* mp_log_levels ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

int mp_msg_find_level(const char *s)
{
    for (int n = 0; n < MP_ARRAY_SIZE(mp_log_levels); n++) {
        if (mp_log_levels[n] && !strcmp(s, mp_log_levels[n]))
            return n;
    }
    return -1;
}