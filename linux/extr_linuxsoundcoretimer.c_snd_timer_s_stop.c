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
struct snd_timer_system_private {int last_expires; scalar_t__ correction; int /*<<< orphan*/  tlist; } ;
struct snd_timer {int sticks; scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,int) ; 

__attribute__((used)) static int snd_timer_s_stop(struct snd_timer * timer)
{
	struct snd_timer_system_private *priv;
	unsigned long jiff;

	priv = (struct snd_timer_system_private *) timer->private_data;
	del_timer(&priv->tlist);
	jiff = jiffies;
	if (time_before(jiff, priv->last_expires))
		timer->sticks = priv->last_expires - jiff;
	else
		timer->sticks = 1;
	priv->correction = 0;
	return 0;
}