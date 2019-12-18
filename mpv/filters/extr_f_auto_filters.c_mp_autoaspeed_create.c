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
struct mp_filter {struct aspeed_priv* priv; } ;
struct TYPE_2__ {void* out; void* in; } ;
struct aspeed_priv {double cur_speed; TYPE_1__ sub; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  aspeed_filter ; 
 void* mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 

struct mp_filter *mp_autoaspeed_create(struct mp_filter *parent)
{
    struct mp_filter *f = mp_filter_create(parent, &aspeed_filter);
    if (!f)
        return NULL;

    struct aspeed_priv *p = f->priv;
    p->cur_speed = 1.0;

    p->sub.in = mp_filter_add_pin(f, MP_PIN_IN, "in");
    p->sub.out = mp_filter_add_pin(f, MP_PIN_OUT, "out");

    return f;
}