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
struct TYPE_2__ {int num_chmaps; int /*<<< orphan*/ * chmaps; } ;
struct priv {int latency; int latency_sec; int bufferlen; int outburst; int buffersize; int /*<<< orphan*/  last_time; TYPE_1__ channel_layouts; int /*<<< orphan*/  untimed; scalar_t__ format; } ;
struct mp_chmap_sel {struct ao* tmp; } ;
struct ao {int samplerate; int period_size; int /*<<< orphan*/  channels; int /*<<< orphan*/  untimed; scalar_t__ format; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ao_chmap_sel_adjust (struct ao*,struct mp_chmap_sel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_chmap_from_channels (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_chmap_sel_add_any (struct mp_chmap_sel*) ; 
 int /*<<< orphan*/  mp_chmap_sel_add_map (struct mp_chmap_sel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_time_sec () ; 

__attribute__((used)) static int init(struct ao *ao)
{
    struct priv *priv = ao->priv;

    if (priv->format)
        ao->format = priv->format;

    ao->untimed = priv->untimed;

    struct mp_chmap_sel sel = {.tmp = ao};
    if (priv->channel_layouts.num_chmaps) {
        for (int n = 0; n < priv->channel_layouts.num_chmaps; n++)
            mp_chmap_sel_add_map(&sel, &priv->channel_layouts.chmaps[n]);
    } else {
        mp_chmap_sel_add_any(&sel);
    }
    if (!ao_chmap_sel_adjust(ao, &sel, &ao->channels))
        mp_chmap_from_channels(&ao->channels, 2);

    priv->latency = priv->latency_sec * ao->samplerate;

    // A "buffer" for this many seconds of audio
    int bursts = (int)(ao->samplerate * priv->bufferlen + 1) / priv->outburst;
    priv->buffersize = priv->outburst * bursts + priv->latency;

    priv->last_time = mp_time_sec();

    ao->period_size = priv->outburst;

    return 0;
}