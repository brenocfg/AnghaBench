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
struct priv {int playing_final; scalar_t__ buffered; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */

__attribute__((used)) static void reset(struct ao *ao)
{
    struct priv *priv = ao->priv;
    priv->buffered = 0;
    priv->playing_final = false;
}