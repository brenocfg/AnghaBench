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
struct mp_autoconvert {struct mp_filter* f; } ;
struct TYPE_2__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct priv {double audio_speed; struct mp_autoconvert public; TYPE_1__ sub; int /*<<< orphan*/  log; } ;
struct mp_filter {int /*<<< orphan*/ * ppins; int /*<<< orphan*/  log; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  autoconvert_filter ; 
 int /*<<< orphan*/  mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 

struct mp_autoconvert *mp_autoconvert_create(struct mp_filter *parent)
{
    struct mp_filter *f = mp_filter_create(parent, &autoconvert_filter);
    if (!f)
        return NULL;

    mp_filter_add_pin(f, MP_PIN_IN, "in");
    mp_filter_add_pin(f, MP_PIN_OUT, "out");

    struct priv *p = f->priv;
    p->public.f = f;
    p->log = f->log;
    p->audio_speed = 1.0;
    p->sub.in = f->ppins[0];
    p->sub.out = f->ppins[1];

    return &p->public;
}