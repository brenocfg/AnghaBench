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
 struct kprobe* ERR_PTR (int) ; 
 int /*<<< orphan*/  KPROBE_FLAG_DISABLED ; 
 struct kprobe* __get_valid_kprobe (struct kprobe*) ; 
 scalar_t__ aggr_kprobe_disabled (struct kprobe*) ; 
 int disarm_kprobe (struct kprobe*,int) ; 
 int /*<<< orphan*/  kprobe_disabled (struct kprobe*) ; 
 int /*<<< orphan*/  kprobes_all_disarmed ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kprobe *__disable_kprobe(struct kprobe *p)
{
	struct kprobe *orig_p;
	int ret;

	/* Get an original kprobe for return */
	orig_p = __get_valid_kprobe(p);
	if (unlikely(orig_p == NULL))
		return ERR_PTR(-EINVAL);

	if (!kprobe_disabled(p)) {
		/* Disable probe if it is a child probe */
		if (p != orig_p)
			p->flags |= KPROBE_FLAG_DISABLED;

		/* Try to disarm and disable this/parent probe */
		if (p == orig_p || aggr_kprobe_disabled(orig_p)) {
			/*
			 * If kprobes_all_disarmed is set, orig_p
			 * should have already been disarmed, so
			 * skip unneed disarming process.
			 */
			if (!kprobes_all_disarmed) {
				ret = disarm_kprobe(orig_p, true);
				if (ret) {
					p->flags &= ~KPROBE_FLAG_DISABLED;
					return ERR_PTR(ret);
				}
			}
			orig_p->flags |= KPROBE_FLAG_DISABLED;
		}
	}

	return orig_p;
}