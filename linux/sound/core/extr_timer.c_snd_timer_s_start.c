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
struct snd_timer_system_private {unsigned long last_jiffies; int correction; unsigned long last_expires; int /*<<< orphan*/  tlist; } ;
struct snd_timer {int sticks; scalar_t__ private_data; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_timer_s_start(struct snd_timer * timer)
{
	struct snd_timer_system_private *priv;
	unsigned long njiff;

	priv = (struct snd_timer_system_private *) timer->private_data;
	njiff = (priv->last_jiffies = jiffies);
	if (priv->correction > timer->sticks - 1) {
		priv->correction -= timer->sticks - 1;
		njiff++;
	} else {
		njiff += timer->sticks - priv->correction;
		priv->correction = 0;
	}
	priv->last_expires = njiff;
	mod_timer(&priv->tlist, njiff);
	return 0;
}