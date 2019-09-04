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
struct priv {scalar_t__ buffered; scalar_t__ latency; int playing_final; scalar_t__ buffersize; int outburst; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int AOPLAY_FINAL_CHUNK ; 
 int MPMIN (scalar_t__,int) ; 
 int /*<<< orphan*/  resume (struct ao*) ; 

__attribute__((used)) static int play(struct ao *ao, void **data, int samples, int flags)
{
    struct priv *priv = ao->priv;
    int accepted;

    resume(ao);

    if (priv->buffered <= 0)
        priv->buffered = priv->latency; // emulate fixed latency

    priv->playing_final = flags & AOPLAY_FINAL_CHUNK;
    if (priv->playing_final) {
        // Last audio chunk - don't round to outburst.
        accepted = MPMIN(priv->buffersize - priv->buffered, samples);
    } else {
        int maxbursts = (priv->buffersize - priv->buffered) / priv->outburst;
        int playbursts = samples / priv->outburst;
        int bursts = playbursts > maxbursts ? maxbursts : playbursts;
        accepted = bursts * priv->outburst;
    }
    priv->buffered += accepted;
    return accepted;
}