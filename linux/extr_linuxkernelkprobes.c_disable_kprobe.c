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
struct kprobe {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct kprobe*) ; 
 int PTR_ERR (struct kprobe*) ; 
 struct kprobe* __disable_kprobe (struct kprobe*) ; 
 int /*<<< orphan*/  kprobe_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int disable_kprobe(struct kprobe *kp)
{
	int ret = 0;
	struct kprobe *p;

	mutex_lock(&kprobe_mutex);

	/* Disable this kprobe */
	p = __disable_kprobe(kp);
	if (IS_ERR(p))
		ret = PTR_ERR(p);

	mutex_unlock(&kprobe_mutex);
	return ret;
}