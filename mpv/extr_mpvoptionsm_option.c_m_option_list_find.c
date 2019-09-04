#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ name; } ;
typedef  TYPE_1__ m_option_t ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,char const*) ; 

const m_option_t *m_option_list_find(const m_option_t *list, const char *name)
{
    for (int i = 0; list[i].name; i++) {
        if (strcmp(list[i].name, name) == 0)
            return &list[i];
    }
    return NULL;
}