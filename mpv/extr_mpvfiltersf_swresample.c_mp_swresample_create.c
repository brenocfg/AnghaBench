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
struct mp_swresample {double speed; struct mp_filter* f; } ;
struct priv {double cmd_speed; struct mp_swresample public; void* out_pool; void* reorder_buffer; TYPE_1__* opts; int /*<<< orphan*/  log; } ;
struct mp_resample_opts {int dummy; } ;
struct mp_filter {int /*<<< orphan*/  global; int /*<<< orphan*/  log; struct priv* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  avopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 void* mp_aframe_pool_create (struct priv*) ; 
 int /*<<< orphan*/  mp_dup_str_array (struct priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 
 TYPE_1__* mp_get_config_group (struct priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resample_conf ; 
 int /*<<< orphan*/  swresample_filter ; 
 TYPE_1__* talloc_dup (struct priv*,struct mp_resample_opts*) ; 

struct mp_swresample *mp_swresample_create(struct mp_filter *parent,
                                           struct mp_resample_opts *opts)
{
    struct mp_filter *f = mp_filter_create(parent, &swresample_filter);
    if (!f)
        return NULL;

    mp_filter_add_pin(f, MP_PIN_IN, "in");
    mp_filter_add_pin(f, MP_PIN_OUT, "out");

    struct priv *p = f->priv;
    p->public.f = f;
    p->public.speed = 1.0;
    p->cmd_speed = 1.0;
    p->log = f->log;

    if (opts) {
        p->opts = talloc_dup(p, opts);
        p->opts->avopts = mp_dup_str_array(p, p->opts->avopts);
    } else {
        p->opts = mp_get_config_group(p, f->global, &resample_conf);
    }

    p->reorder_buffer = mp_aframe_pool_create(p);
    p->out_pool = mp_aframe_pool_create(p);

    return &p->public;
}