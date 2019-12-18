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
struct priv {double buffered; double speed; int /*<<< orphan*/  paused; } ;
struct ao {double samplerate; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  drain (struct ao*) ; 
 int /*<<< orphan*/  mp_sleep_us (double) ; 

__attribute__((used)) static void wait_drain(struct ao *ao)
{
    struct priv *priv = ao->priv;
    drain(ao);
    if (!priv->paused)
        mp_sleep_us(1000000.0 * priv->buffered / ao->samplerate / priv->speed);
}