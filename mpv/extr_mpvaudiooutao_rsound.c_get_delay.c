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
struct priv {int /*<<< orphan*/  rd; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 double rsd_delay_ms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double get_delay(struct ao *ao)
{
    struct priv *priv = ao->priv;
    return rsd_delay_ms(priv->rd) / 1000.0;
}