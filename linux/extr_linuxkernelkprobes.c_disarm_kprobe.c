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
 int /*<<< orphan*/  __disarm_kprobe (struct kprobe*,int) ; 
 int /*<<< orphan*/  cpus_read_lock () ; 
 int /*<<< orphan*/  cpus_read_unlock () ; 
 int disarm_kprobe_ftrace (struct kprobe*) ; 
 int /*<<< orphan*/  kprobe_ftrace (struct kprobe*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_mutex ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disarm_kprobe(struct kprobe *kp, bool reopt)
{
	if (unlikely(kprobe_ftrace(kp)))
		return disarm_kprobe_ftrace(kp);

	cpus_read_lock();
	mutex_lock(&text_mutex);
	__disarm_kprobe(kp, reopt);
	mutex_unlock(&text_mutex);
	cpus_read_unlock();

	return 0;
}