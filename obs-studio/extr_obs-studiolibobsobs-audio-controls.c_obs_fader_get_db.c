#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float cur_db; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ obs_fader_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

float obs_fader_get_db(obs_fader_t *fader)
{
	if (!fader)
		return 0.0f;

	pthread_mutex_lock(&fader->mutex);
	const float db = fader->cur_db;
	pthread_mutex_unlock(&fader->mutex);

	return db;
}