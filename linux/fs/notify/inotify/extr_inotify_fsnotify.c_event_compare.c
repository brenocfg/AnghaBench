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
struct inotify_event_info {int mask; scalar_t__ name_len; int /*<<< orphan*/  name; } ;
struct fsnotify_event {scalar_t__ inode; } ;

/* Variables and functions */
 int FS_IN_IGNORED ; 
 struct inotify_event_info* INOTIFY_E (struct fsnotify_event*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool event_compare(struct fsnotify_event *old_fsn,
			  struct fsnotify_event *new_fsn)
{
	struct inotify_event_info *old, *new;

	old = INOTIFY_E(old_fsn);
	new = INOTIFY_E(new_fsn);
	if (old->mask & FS_IN_IGNORED)
		return false;
	if ((old->mask == new->mask) &&
	    (old_fsn->inode == new_fsn->inode) &&
	    (old->name_len == new->name_len) &&
	    (!old->name_len || !strcmp(old->name, new->name)))
		return true;
	return false;
}