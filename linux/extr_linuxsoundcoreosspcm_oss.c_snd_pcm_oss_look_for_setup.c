#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_oss_setup {int /*<<< orphan*/  task_name; struct snd_pcm_oss_setup* next; } ;
struct snd_pcm {TYPE_2__* streams; } ;
struct TYPE_3__ {int /*<<< orphan*/  setup_mutex; struct snd_pcm_oss_setup* setup_list; } ;
struct TYPE_4__ {TYPE_1__ oss; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* strip_task_path (char const*) ; 

__attribute__((used)) static void snd_pcm_oss_look_for_setup(struct snd_pcm *pcm, int stream,
				      const char *task_name,
				      struct snd_pcm_oss_setup *rsetup)
{
	struct snd_pcm_oss_setup *setup;

	mutex_lock(&pcm->streams[stream].oss.setup_mutex);
	do {
		for (setup = pcm->streams[stream].oss.setup_list; setup;
		     setup = setup->next) {
			if (!strcmp(setup->task_name, task_name))
				goto out;
		}
	} while ((task_name = strip_task_path(task_name)) != NULL);
 out:
	if (setup)
		*rsetup = *setup;
	mutex_unlock(&pcm->streams[stream].oss.setup_mutex);
}