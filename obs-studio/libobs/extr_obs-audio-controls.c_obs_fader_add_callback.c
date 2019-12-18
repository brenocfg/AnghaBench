#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fader_cb {void* member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  callback_mutex; int /*<<< orphan*/  callbacks; } ;
typedef  TYPE_1__ obs_fader_t ;
typedef  int /*<<< orphan*/  obs_fader_changed_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct fader_cb*) ; 
 int /*<<< orphan*/  obs_ptr_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_fader_add_callback(obs_fader_t *fader, obs_fader_changed_t callback,
			    void *param)
{
	struct fader_cb cb = {callback, param};

	if (!obs_ptr_valid(fader, "obs_fader_add_callback"))
		return;

	pthread_mutex_lock(&fader->callback_mutex);
	da_push_back(fader->callbacks, &cb);
	pthread_mutex_unlock(&fader->callback_mutex);
}