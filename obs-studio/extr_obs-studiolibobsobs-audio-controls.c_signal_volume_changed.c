#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t num; struct fader_cb* array; } ;
struct obs_fader {int /*<<< orphan*/  callback_mutex; TYPE_1__ callbacks; } ;
struct fader_cb {int /*<<< orphan*/  param; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,float const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,float const) ; 

__attribute__((used)) static void signal_volume_changed(struct obs_fader *fader, const float db)
{
	pthread_mutex_lock(&fader->callback_mutex);
	for (size_t i = fader->callbacks.num; i > 0; i--) {
		struct fader_cb cb = fader->callbacks.array[i - 1];
		cb.callback(cb.param, db);
	}
	pthread_mutex_unlock(&fader->callback_mutex);
}