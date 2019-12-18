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
struct synth_event {int /*<<< orphan*/  devent; scalar_t__ ref; } ;

/* Variables and functions */
 int EBUSY ; 
 int ECANCELED ; 
 int EINVAL ; 
 int ENOENT ; 
 int __create_synth_event (int,char const*,char const**) ; 
 int /*<<< orphan*/  dyn_event_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_mutex ; 
 struct synth_event* find_synth_event (char const*) ; 
 int /*<<< orphan*/  free_synth_event (struct synth_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int unregister_synth_event (struct synth_event*) ; 

__attribute__((used)) static int create_or_delete_synth_event(int argc, char **argv)
{
	const char *name = argv[0];
	struct synth_event *event = NULL;
	int ret;

	/* trace_run_command() ensures argc != 0 */
	if (name[0] == '!') {
		mutex_lock(&event_mutex);
		event = find_synth_event(name + 1);
		if (event) {
			if (event->ref)
				ret = -EBUSY;
			else {
				ret = unregister_synth_event(event);
				if (!ret) {
					dyn_event_remove(&event->devent);
					free_synth_event(event);
				}
			}
		} else
			ret = -ENOENT;
		mutex_unlock(&event_mutex);
		return ret;
	}

	ret = __create_synth_event(argc - 1, name, (const char **)argv + 1);
	return ret == -ECANCELED ? -EINVAL : ret;
}