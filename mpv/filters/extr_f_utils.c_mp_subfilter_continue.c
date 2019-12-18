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
struct mp_subfilter {int /*<<< orphan*/  frame; struct mp_pin* out; TYPE_1__* filter; } ;
struct mp_pin {int dummy; } ;
struct TYPE_2__ {struct mp_pin** pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NO_FRAME ; 
 int /*<<< orphan*/  mark_progress (struct mp_subfilter*) ; 
 int /*<<< orphan*/  mp_pin_in_needs_data (struct mp_pin*) ; 
 int /*<<< orphan*/  mp_pin_in_write (struct mp_pin*,int /*<<< orphan*/ ) ; 

void mp_subfilter_continue(struct mp_subfilter *sub)
{
    struct mp_pin *out = sub->filter ? sub->filter->pins[0] : sub->out;
    // It was made sure earlier that the pin is writable, unless the filter
    // was newly created, or a previously existing filter (which was going to
    // accept input) was destroyed. In those cases, essentially restart
    // data flow.
    if (!mp_pin_in_needs_data(out)) {
        mark_progress(sub);
        return;
    }
    mp_pin_in_write(out, sub->frame);
    sub->frame = MP_NO_FRAME;
}