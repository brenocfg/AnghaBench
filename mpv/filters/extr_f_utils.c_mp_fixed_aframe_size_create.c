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
struct mp_filter {struct fixed_aframe_size_priv* priv; } ;
struct fixed_aframe_size_priv {int samples; int pad_silence; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  fixed_aframe_size_filter ; 
 int /*<<< orphan*/  mp_aframe_pool_create (struct fixed_aframe_size_priv*) ; 
 int /*<<< orphan*/  mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 

struct mp_filter *mp_fixed_aframe_size_create(struct mp_filter *parent,
                                              int samples, bool pad_silence)
{
    if (samples < 1)
        return NULL;

    struct mp_filter *f = mp_filter_create(parent, &fixed_aframe_size_filter);
    if (!f)
        return NULL;

    mp_filter_add_pin(f, MP_PIN_IN, "in");
    mp_filter_add_pin(f, MP_PIN_OUT, "out");

    struct fixed_aframe_size_priv *p = f->priv;
    p->samples = samples;
    p->pad_silence = pad_silence;
    p->pool = mp_aframe_pool_create(p);

    return f;
}