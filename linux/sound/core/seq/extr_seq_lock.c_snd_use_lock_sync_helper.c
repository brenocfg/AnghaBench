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
typedef  int /*<<< orphan*/  snd_use_lock_t ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

void snd_use_lock_sync_helper(snd_use_lock_t *lockp, const char *file, int line)
{
	int warn_count = 5 * HZ;

	if (atomic_read(lockp) < 0) {
		pr_warn("ALSA: seq_lock: lock trouble [counter = %d] in %s:%d\n", atomic_read(lockp), file, line);
		return;
	}
	while (atomic_read(lockp) > 0) {
		if (warn_count-- == 0)
			pr_warn("ALSA: seq_lock: waiting [%d left] in %s:%d\n", atomic_read(lockp), file, line);
		schedule_timeout_uninterruptible(1);
	}
}