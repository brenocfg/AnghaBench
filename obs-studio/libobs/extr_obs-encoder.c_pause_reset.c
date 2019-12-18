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
struct pause_data {int /*<<< orphan*/  mutex; scalar_t__ ts_offset; scalar_t__ ts_end; scalar_t__ ts_start; scalar_t__ last_video_ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void pause_reset(struct pause_data *pause)
{
	pthread_mutex_lock(&pause->mutex);
	pause->last_video_ts = 0;
	pause->ts_start = 0;
	pause->ts_end = 0;
	pause->ts_offset = 0;
	pthread_mutex_unlock(&pause->mutex);
}