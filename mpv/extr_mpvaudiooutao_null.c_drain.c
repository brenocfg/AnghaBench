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
struct priv {scalar_t__ buffered; double last_time; double speed; int /*<<< orphan*/  playing_final; scalar_t__ paused; } ;
struct ao {double samplerate; scalar_t__ untimed; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct ao*,char*) ; 
 double mp_time_sec () ; 

__attribute__((used)) static void drain(struct ao *ao)
{
    struct priv *priv = ao->priv;

    if (ao->untimed) {
        priv->buffered = 0;
        return;
    }

    if (priv->paused)
        return;

    double now = mp_time_sec();
    if (priv->buffered > 0) {
        priv->buffered -= (now - priv->last_time) * ao->samplerate * priv->speed;
        if (priv->buffered < 0) {
            if (!priv->playing_final)
                MP_ERR(ao, "buffer underrun\n");
            priv->buffered = 0;
        }
    }
    priv->last_time = now;
}