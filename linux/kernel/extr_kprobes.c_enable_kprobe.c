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
struct kprobe {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KPROBE_FLAG_DISABLED ; 
 struct kprobe* __get_valid_kprobe (struct kprobe*) ; 
 int arm_kprobe (struct kprobe*) ; 
 scalar_t__ kprobe_disabled (struct kprobe*) ; 
 scalar_t__ kprobe_gone (struct kprobe*) ; 
 int /*<<< orphan*/  kprobe_mutex ; 
 int /*<<< orphan*/  kprobes_all_disarmed ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int enable_kprobe(struct kprobe *kp)
{
	int ret = 0;
	struct kprobe *p;

	mutex_lock(&kprobe_mutex);

	/* Check whether specified probe is valid. */
	p = __get_valid_kprobe(kp);
	if (unlikely(p == NULL)) {
		ret = -EINVAL;
		goto out;
	}

	if (kprobe_gone(kp)) {
		/* This kprobe has gone, we couldn't enable it. */
		ret = -EINVAL;
		goto out;
	}

	if (p != kp)
		kp->flags &= ~KPROBE_FLAG_DISABLED;

	if (!kprobes_all_disarmed && kprobe_disabled(p)) {
		p->flags &= ~KPROBE_FLAG_DISABLED;
		ret = arm_kprobe(p);
		if (ret)
			p->flags |= KPROBE_FLAG_DISABLED;
	}
out:
	mutex_unlock(&kprobe_mutex);
	return ret;
}