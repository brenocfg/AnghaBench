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
struct obs_scene {int /*<<< orphan*/  audio_mutex; int /*<<< orphan*/  video_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct obs_scene*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_all_items (struct obs_scene*) ; 

__attribute__((used)) static void scene_destroy(void *data)
{
	struct obs_scene *scene = data;

	remove_all_items(scene);

	pthread_mutex_destroy(&scene->video_mutex);
	pthread_mutex_destroy(&scene->audio_mutex);
	bfree(scene);
}