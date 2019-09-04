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
struct priv {double buffered; double latency; double outburst; scalar_t__ broken_delay; scalar_t__ broken_eof; } ;
struct ao {double samplerate; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  drain (struct ao*) ; 

__attribute__((used)) static double get_delay(struct ao *ao)
{
    struct priv *priv = ao->priv;

    drain(ao);

    // Note how get_delay returns the delay in audio device time (instead of
    // adjusting for speed), since most AOs seem to also do that.
    double delay = priv->buffered;

    // Drivers with broken EOF handling usually always report the same device-
    // level delay that is additional to the buffer time.
    if (priv->broken_eof && priv->buffered < priv->latency)
        delay = priv->latency;

    delay /= ao->samplerate;

    if (priv->broken_delay) { // Report only multiples of outburst
        double q = priv->outburst / (double)ao->samplerate;
        if (delay > 0)
            delay = (int)(delay / q) * q;
    }

    return delay;
}