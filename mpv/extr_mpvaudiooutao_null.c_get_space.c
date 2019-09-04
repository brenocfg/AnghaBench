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
struct priv {int buffersize; int latency; int buffered; int outburst; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  drain (struct ao*) ; 

__attribute__((used)) static int get_space(struct ao *ao)
{
    struct priv *priv = ao->priv;

    drain(ao);
    int samples = priv->buffersize - priv->latency - priv->buffered;
    return samples / priv->outburst * priv->outburst;
}