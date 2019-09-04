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
struct obs_volmeter {int type; int /*<<< orphan*/  callback_mutex; int /*<<< orphan*/  mutex; } ;
typedef  struct obs_volmeter obs_volmeter_t ;
typedef  enum obs_fader_type { ____Placeholder_obs_fader_type } obs_fader_type ;

/* Variables and functions */
 struct obs_volmeter* bzalloc (int) ; 
 int /*<<< orphan*/  obs_volmeter_destroy (struct obs_volmeter*) ; 
 int /*<<< orphan*/  obs_volmeter_set_update_interval (struct obs_volmeter*,int) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 

obs_volmeter_t *obs_volmeter_create(enum obs_fader_type type)
{
	struct obs_volmeter *volmeter = bzalloc(sizeof(struct obs_volmeter));
	if (!volmeter)
		return NULL;

	pthread_mutex_init_value(&volmeter->mutex);
	pthread_mutex_init_value(&volmeter->callback_mutex);
	if (pthread_mutex_init(&volmeter->mutex, NULL) != 0)
		goto fail;
	if (pthread_mutex_init(&volmeter->callback_mutex, NULL) != 0)
		goto fail;

	volmeter->type = type;

	obs_volmeter_set_update_interval(volmeter, 50);

	return volmeter;
fail:
	obs_volmeter_destroy(volmeter);
	return NULL;
}