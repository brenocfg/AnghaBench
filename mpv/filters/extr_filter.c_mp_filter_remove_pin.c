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
struct mp_pin {struct mp_pin* other; struct mp_filter* owner; } ;
struct mp_filter {int num_pins; struct mp_pin** ppins; struct mp_pin** pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct mp_pin**,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_pin_disconnect (struct mp_pin*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_pin*) ; 

void mp_filter_remove_pin(struct mp_filter *f, struct mp_pin *p)
{
    if (!p)
        return;

    assert(p->owner == f);
    mp_pin_disconnect(p);
    mp_pin_disconnect(p->other);

    int index = -1;
    for (int n = 0; n < f->num_pins; n++) {
        if (f->ppins[n] == p) {
            index = n;
            break;
        }
    }
    assert(index >= 0);

    talloc_free(f->pins[index]);
    talloc_free(f->ppins[index]);

    int count = f->num_pins;
    MP_TARRAY_REMOVE_AT(f->pins, count, index);
    count = f->num_pins;
    MP_TARRAY_REMOVE_AT(f->ppins, count, index);
    f->num_pins -= 1;
}