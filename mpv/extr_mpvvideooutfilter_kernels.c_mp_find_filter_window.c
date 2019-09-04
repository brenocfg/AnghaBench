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
struct filter_window {scalar_t__ name; } ;

/* Variables and functions */
 struct filter_window* mp_filter_windows ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

const struct filter_window *mp_find_filter_window(const char *name)
{
    if (!name)
        return NULL;
    for (const struct filter_window *w = mp_filter_windows; w->name; w++) {
        if (strcmp(w->name, name) == 0)
            return w;
    }
    return NULL;
}