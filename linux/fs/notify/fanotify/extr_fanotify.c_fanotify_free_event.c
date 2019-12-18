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
struct fsnotify_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext_fh; } ;
struct fanotify_event {int /*<<< orphan*/  mask; int /*<<< orphan*/  pid; TYPE_1__ fid; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 struct fanotify_event* FANOTIFY_E (struct fsnotify_event*) ; 
 struct fanotify_event* FANOTIFY_PE (struct fsnotify_event*) ; 
 int /*<<< orphan*/  fanotify_event_cachep ; 
 scalar_t__ fanotify_event_has_ext_fh (struct fanotify_event*) ; 
 scalar_t__ fanotify_event_has_path (struct fanotify_event*) ; 
 scalar_t__ fanotify_is_perm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fanotify_perm_event_cachep ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fanotify_event*) ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fanotify_free_event(struct fsnotify_event *fsn_event)
{
	struct fanotify_event *event;

	event = FANOTIFY_E(fsn_event);
	if (fanotify_event_has_path(event))
		path_put(&event->path);
	else if (fanotify_event_has_ext_fh(event))
		kfree(event->fid.ext_fh);
	put_pid(event->pid);
	if (fanotify_is_perm_event(event->mask)) {
		kmem_cache_free(fanotify_perm_event_cachep,
				FANOTIFY_PE(fsn_event));
		return;
	}
	kmem_cache_free(fanotify_event_cachep, event);
}