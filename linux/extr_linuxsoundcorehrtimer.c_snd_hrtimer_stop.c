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
struct snd_timer {struct snd_hrtimer* private_data; } ;
struct snd_hrtimer {int /*<<< orphan*/  hrt; scalar_t__ in_callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hrtimer_stop(struct snd_timer *t)
{
	struct snd_hrtimer *stime = t->private_data;

	if (stime->in_callback)
		return 0;
	hrtimer_try_to_cancel(&stime->hrt);
	return 0;
}