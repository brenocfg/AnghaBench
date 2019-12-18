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
struct m_obj_settings {scalar_t__ name; scalar_t__ enabled; scalar_t__* attribs; scalar_t__ label; } ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool compare_filter(struct m_obj_settings *a, struct m_obj_settings *b)
{
    if (a == b || !a || !b)
        return a == b;

    if (!a->name || !b->name)
        return a->name == b->name;

    if (!!a->label != !!b->label || (a->label && strcmp(a->label, b->label) != 0))
        return false;

    if (a->enabled != b->enabled)
        return false;

    if (!a->attribs || !a->attribs[0])
        return !b->attribs || !b->attribs[0];

    for (int n = 0; a->attribs[n] || b->attribs[n]; n++) {
        if (!a->attribs[n] || !b->attribs[n])
            return false;
        if (strcmp(a->attribs[n], b->attribs[n]) != 0)
            return false;
    }

    return true;
}