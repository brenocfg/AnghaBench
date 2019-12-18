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
struct obs_fader {int ignore_next_signal; float cur_db; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  calldata_t ;

/* Variables and functions */
 scalar_t__ calldata_float (int /*<<< orphan*/ *,char*) ; 
 float mul_to_db (float const) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_volume_changed (struct obs_fader*,float const) ; 

__attribute__((used)) static void fader_source_volume_changed(void *vptr, calldata_t *calldata)
{
	struct obs_fader *fader = (struct obs_fader *)vptr;

	pthread_mutex_lock(&fader->mutex);

	if (fader->ignore_next_signal) {
		fader->ignore_next_signal = false;
		pthread_mutex_unlock(&fader->mutex);
		return;
	}

	const float mul = (float)calldata_float(calldata, "volume");
	const float db = mul_to_db(mul);
	fader->cur_db = db;

	pthread_mutex_unlock(&fader->mutex);

	signal_volume_changed(fader, db);
}