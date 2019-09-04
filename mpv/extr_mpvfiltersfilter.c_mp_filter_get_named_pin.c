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
struct mp_pin {int /*<<< orphan*/  name; } ;
struct mp_filter {int num_pins; struct mp_pin** pins; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct mp_pin *mp_filter_get_named_pin(struct mp_filter *f, const char *name)
{
    for (int n = 0; n < f->num_pins; n++) {
        if (name && strcmp(f->pins[n]->name, name) == 0)
            return f->pins[n];
    }
    return NULL;
}