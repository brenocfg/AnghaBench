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
struct sh_stream {int dummy; } ;
struct priv {struct sh_stream* src; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  demux_filter ; 
 int /*<<< orphan*/  demux_set_stream_wakeup_cb (struct sh_stream*,int /*<<< orphan*/ ,struct mp_filter*) ; 
 int /*<<< orphan*/  mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup ; 

struct mp_filter *mp_demux_in_create(struct mp_filter *parent,
                                     struct sh_stream *src)
{
    struct mp_filter *f = mp_filter_create(parent, &demux_filter);
    if (!f)
        return NULL;

    struct priv *p = f->priv;
    p->src = src;

    mp_filter_add_pin(f, MP_PIN_OUT, "out");

    demux_set_stream_wakeup_cb(p->src, wakeup, f);

    return f;
}