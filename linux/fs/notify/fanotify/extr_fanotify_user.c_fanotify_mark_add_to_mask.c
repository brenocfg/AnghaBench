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
struct fsnotify_mark {int mask; int ignored_mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
typedef  int __u32 ;

/* Variables and functions */
 unsigned int FAN_MARK_IGNORED_MASK ; 
 unsigned int FAN_MARK_IGNORED_SURV_MODIFY ; 
 int /*<<< orphan*/  FSNOTIFY_MARK_FLAG_IGNORED_SURV_MODIFY ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __u32 fanotify_mark_add_to_mask(struct fsnotify_mark *fsn_mark,
				       __u32 mask,
				       unsigned int flags)
{
	__u32 oldmask = -1;

	spin_lock(&fsn_mark->lock);
	if (!(flags & FAN_MARK_IGNORED_MASK)) {
		oldmask = fsn_mark->mask;
		fsn_mark->mask |= mask;
	} else {
		fsn_mark->ignored_mask |= mask;
		if (flags & FAN_MARK_IGNORED_SURV_MODIFY)
			fsn_mark->flags |= FSNOTIFY_MARK_FLAG_IGNORED_SURV_MODIFY;
	}
	spin_unlock(&fsn_mark->lock);

	return mask & ~oldmask;
}