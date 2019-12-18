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
struct priv {int pending; int /*<<< orphan*/  pitch; int /*<<< orphan*/  speed; int /*<<< orphan*/  cur_format; scalar_t__ rubber; TYPE_1__* opts; } ;
struct mp_filter {struct priv* priv; } ;
struct TYPE_2__ {int transients; int detector; int phase; int window; int smoothing; int formant; int pitch; int channels; } ;

/* Variables and functions */
 scalar_t__ AF_FORMAT_FLOATP ; 
 int /*<<< orphan*/  MP_FATAL (struct mp_filter*,char*) ; 
 int RubberBandOptionProcessRealTime ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_aframe_config_copy (int /*<<< orphan*/ ,int) ; 
 int mp_aframe_get_channels (int) ; 
 scalar_t__ mp_aframe_get_format (int) ; 
 int mp_aframe_get_rate (int) ; 
 scalar_t__ rubberband_new (int,int,int,double,double) ; 
 int /*<<< orphan*/  update_pitch (struct priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_speed (struct priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool init_rubberband(struct mp_filter *f)
{
    struct priv *p = f->priv;

    assert(!p->rubber);
    assert(p->pending);

    int opts = p->opts->transients | p->opts->detector | p->opts->phase |
               p->opts->window | p->opts->smoothing | p->opts->formant |
               p->opts->pitch | p-> opts->channels |
               RubberBandOptionProcessRealTime;

    int rate = mp_aframe_get_rate(p->pending);
    int channels = mp_aframe_get_channels(p->pending);
    if (mp_aframe_get_format(p->pending) != AF_FORMAT_FLOATP)
        return false;

    p->rubber = rubberband_new(rate, channels, opts, 1.0, 1.0);
    if (!p->rubber) {
        MP_FATAL(f, "librubberband initialization failed.\n");
        return false;
    }

    mp_aframe_config_copy(p->cur_format, p->pending);

    update_speed(p, p->speed);
    update_pitch(p, p->pitch);

    return true;
}