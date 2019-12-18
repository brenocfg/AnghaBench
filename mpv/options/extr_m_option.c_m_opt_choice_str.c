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
struct m_opt_choice_alternatives {char const* name; int value; } ;

/* Variables and functions */

const char *m_opt_choice_str(const struct m_opt_choice_alternatives *choices,
                             int value)
{
    for (const struct m_opt_choice_alternatives *c = choices; c->name; c++) {
        if (c->value == value)
            return c->name;
    }
    return NULL;
}