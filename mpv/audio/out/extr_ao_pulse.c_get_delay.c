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
struct priv {scalar_t__ cfg_latency_hacks; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 double get_delay_hackfixed (struct ao*) ; 
 double get_delay_pulse (struct ao*) ; 

__attribute__((used)) static double get_delay(struct ao *ao)
{
    struct priv *priv = ao->priv;
    if (priv->cfg_latency_hacks) {
        return get_delay_hackfixed(ao);
    } else {
        return get_delay_pulse(ao);
    }
}