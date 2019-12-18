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
struct wakelock {int /*<<< orphan*/  ws; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_BLOCK_SUSPEND ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct wakelock*) ; 
 int PTR_ERR (struct wakelock*) ; 
 int /*<<< orphan*/  __pm_relax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 
 struct wakelock* wakelock_lookup_add (char const*,size_t,int) ; 
 int /*<<< orphan*/  wakelocks_gc () ; 
 int /*<<< orphan*/  wakelocks_lock ; 
 int /*<<< orphan*/  wakelocks_lru_most_recent (struct wakelock*) ; 

int pm_wake_unlock(const char *buf)
{
	struct wakelock *wl;
	size_t len;
	int ret = 0;

	if (!capable(CAP_BLOCK_SUSPEND))
		return -EPERM;

	len = strlen(buf);
	if (!len)
		return -EINVAL;

	if (buf[len-1] == '\n')
		len--;

	if (!len)
		return -EINVAL;

	mutex_lock(&wakelocks_lock);

	wl = wakelock_lookup_add(buf, len, false);
	if (IS_ERR(wl)) {
		ret = PTR_ERR(wl);
		goto out;
	}
	__pm_relax(wl->ws);

	wakelocks_lru_most_recent(wl);
	wakelocks_gc();

 out:
	mutex_unlock(&wakelocks_lock);
	return ret;
}