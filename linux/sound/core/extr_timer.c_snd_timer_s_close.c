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
struct snd_timer_system_private {int /*<<< orphan*/  tlist; } ;
struct snd_timer {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_timer_s_close(struct snd_timer *timer)
{
	struct snd_timer_system_private *priv;

	priv = (struct snd_timer_system_private *)timer->private_data;
	del_timer_sync(&priv->tlist);
	return 0;
}