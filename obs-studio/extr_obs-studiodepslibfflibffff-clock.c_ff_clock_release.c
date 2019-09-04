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
struct ff_clock {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  retain; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (struct ff_clock*) ; 
 scalar_t__ ff_atomic_dec_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void ff_clock_release(struct ff_clock **clock)
{
	if (ff_atomic_dec_long(&(*clock)->retain) == 0) {
		pthread_cond_destroy(&(*clock)->cond);
		pthread_mutex_destroy(&(*clock)->mutex);
		av_free(*clock);
	}

	*clock = NULL;
}