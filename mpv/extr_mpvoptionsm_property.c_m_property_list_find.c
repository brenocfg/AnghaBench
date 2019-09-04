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
struct m_property {scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,char const*) ; 

struct m_property *m_property_list_find(const struct m_property *list,
                                        const char *name)
{
    for (int n = 0; list && list[n].name; n++) {
        if (strcmp(list[n].name, name) == 0)
            return (struct m_property *)&list[n];
    }
    return NULL;
}