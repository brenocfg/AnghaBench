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
struct TYPE_2__ {void* out; void* in; } ;
struct rotate_priv {int prev_rotate; TYPE_1__ sub; } ;
struct mp_filter {struct rotate_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 void* mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rotate_filter ; 

struct mp_filter *mp_autorotate_create(struct mp_filter *parent)
{
    struct mp_filter *f = mp_filter_create(parent, &rotate_filter);
    if (!f)
        return NULL;

    struct rotate_priv *p = f->priv;
    p->prev_rotate = -1;

    p->sub.in = mp_filter_add_pin(f, MP_PIN_IN, "in");
    p->sub.out = mp_filter_add_pin(f, MP_PIN_OUT, "out");

    return f;
}