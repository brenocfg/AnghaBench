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
struct kprobe {int flags; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int KPROBE_FLAG_DISABLED ; 
 int KPROBE_FLAG_GONE ; 
 int add_new_kprobe (struct kprobe*,struct kprobe*) ; 
 struct kprobe* alloc_aggr_kprobe (struct kprobe*) ; 
 int arch_prepare_kprobe (struct kprobe*) ; 
 int arm_kprobe (struct kprobe*) ; 
 int /*<<< orphan*/  copy_kprobe (struct kprobe*,struct kprobe*) ; 
 int /*<<< orphan*/  cpus_read_lock () ; 
 int /*<<< orphan*/  cpus_read_unlock () ; 
 int /*<<< orphan*/  init_aggr_kprobe (struct kprobe*,struct kprobe*) ; 
 int /*<<< orphan*/  jump_label_lock () ; 
 int /*<<< orphan*/  jump_label_unlock () ; 
 int /*<<< orphan*/  kprobe_aggrprobe (struct kprobe*) ; 
 scalar_t__ kprobe_disabled (struct kprobe*) ; 
 scalar_t__ kprobe_gone (struct kprobe*) ; 
 scalar_t__ kprobe_unused (struct kprobe*) ; 
 int /*<<< orphan*/  kprobes_all_disarmed ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_optimized_kprobe (struct kprobe*) ; 
 int reuse_unused_kprobe (struct kprobe*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  text_mutex ; 

__attribute__((used)) static int register_aggr_kprobe(struct kprobe *orig_p, struct kprobe *p)
{
	int ret = 0;
	struct kprobe *ap = orig_p;

	cpus_read_lock();

	/* For preparing optimization, jump_label_text_reserved() is called */
	jump_label_lock();
	mutex_lock(&text_mutex);

	if (!kprobe_aggrprobe(orig_p)) {
		/* If orig_p is not an aggr_kprobe, create new aggr_kprobe. */
		ap = alloc_aggr_kprobe(orig_p);
		if (!ap) {
			ret = -ENOMEM;
			goto out;
		}
		init_aggr_kprobe(ap, orig_p);
	} else if (kprobe_unused(ap)) {
		/* This probe is going to die. Rescue it */
		ret = reuse_unused_kprobe(ap);
		if (ret)
			goto out;
	}

	if (kprobe_gone(ap)) {
		/*
		 * Attempting to insert new probe at the same location that
		 * had a probe in the module vaddr area which already
		 * freed. So, the instruction slot has already been
		 * released. We need a new slot for the new probe.
		 */
		ret = arch_prepare_kprobe(ap);
		if (ret)
			/*
			 * Even if fail to allocate new slot, don't need to
			 * free aggr_probe. It will be used next time, or
			 * freed by unregister_kprobe.
			 */
			goto out;

		/* Prepare optimized instructions if possible. */
		prepare_optimized_kprobe(ap);

		/*
		 * Clear gone flag to prevent allocating new slot again, and
		 * set disabled flag because it is not armed yet.
		 */
		ap->flags = (ap->flags & ~KPROBE_FLAG_GONE)
			    | KPROBE_FLAG_DISABLED;
	}

	/* Copy ap's insn slot to p */
	copy_kprobe(ap, p);
	ret = add_new_kprobe(ap, p);

out:
	mutex_unlock(&text_mutex);
	jump_label_unlock();
	cpus_read_unlock();

	if (ret == 0 && kprobe_disabled(ap) && !kprobe_disabled(p)) {
		ap->flags &= ~KPROBE_FLAG_DISABLED;
		if (!kprobes_all_disarmed) {
			/* Arm the breakpoint again. */
			ret = arm_kprobe(ap);
			if (ret) {
				ap->flags |= KPROBE_FLAG_DISABLED;
				list_del_rcu(&p->list);
				synchronize_rcu();
			}
		}
	}
	return ret;
}