#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_sws_filter {int /*<<< orphan*/  pool; TYPE_1__* sws; struct mp_filter* f; } ;
struct mp_filter {int /*<<< orphan*/  global; int /*<<< orphan*/  log; struct mp_sws_filter* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_image_pool_new (struct mp_sws_filter*) ; 
 TYPE_1__* mp_sws_alloc (struct mp_sws_filter*) ; 
 int /*<<< orphan*/  mp_sws_enable_cmdline_opts (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sws_filter ; 

struct mp_sws_filter *mp_sws_filter_create(struct mp_filter *parent)
{
    struct mp_filter *f = mp_filter_create(parent, &sws_filter);
    if (!f)
        return NULL;

    mp_filter_add_pin(f, MP_PIN_IN, "in");
    mp_filter_add_pin(f, MP_PIN_OUT, "out");

    struct mp_sws_filter *s = f->priv;
    s->f = f;
    s->sws = mp_sws_alloc(s);
    s->sws->log = f->log;
    mp_sws_enable_cmdline_opts(s->sws, f->global);
    s->pool = mp_image_pool_new(s);

    return s;
}