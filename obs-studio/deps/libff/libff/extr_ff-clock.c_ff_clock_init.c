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
struct ff_clock {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (struct ff_clock*) ; 
 struct ff_clock* av_mallocz (int) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct ff_clock *ff_clock_init(void)
{
	struct ff_clock *clock = av_mallocz(sizeof(struct ff_clock));

	if (clock == NULL)
		return NULL;

	if (pthread_mutex_init(&clock->mutex, NULL) != 0)
		goto fail;

	if (pthread_cond_init(&clock->cond, NULL) != 0)
		goto fail1;

	return clock;

fail1:
	pthread_mutex_destroy(&clock->mutex);
fail:
	av_free(clock);

	return NULL;
}