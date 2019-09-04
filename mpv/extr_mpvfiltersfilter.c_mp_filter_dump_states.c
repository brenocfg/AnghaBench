#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mp_filter {int num_pins; TYPE_1__* in; int /*<<< orphan*/ * ppins; int /*<<< orphan*/ * pins; } ;
struct TYPE_2__ {int num_children; struct mp_filter** children; struct mp_filter* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct mp_filter*,char*,int /*<<< orphan*/ ,struct mp_filter*,int /*<<< orphan*/ ,struct mp_filter*) ; 
 int /*<<< orphan*/  dump_pin_state (struct mp_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filt_name (struct mp_filter*) ; 

void mp_filter_dump_states(struct mp_filter *f)
{
    MP_WARN(f, "%s[%p] (%s[%p])\n", filt_name(f), f,
            filt_name(f->in->parent), f->in->parent);
    for (int n = 0; n < f->num_pins; n++) {
        dump_pin_state(f, f->pins[n]);
        dump_pin_state(f, f->ppins[n]);
    }

    for (int n = 0; n < f->in->num_children; n++)
        mp_filter_dump_states(f->in->children[n]);
}