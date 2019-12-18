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
typedef  scalar_t__ u64 ;
struct wakelock {int /*<<< orphan*/  ws; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_BLOCK_SUSPEND ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct wakelock*) ; 
 scalar_t__ NSEC_PER_MSEC ; 
 int PTR_ERR (struct wakelock*) ; 
 int /*<<< orphan*/  __pm_stay_awake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pm_wakeup_event (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  isspace (char const) ; 
 int kstrtou64 (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_spaces (char const*) ; 
 struct wakelock* wakelock_lookup_add (char const*,size_t,int) ; 
 int /*<<< orphan*/  wakelocks_lock ; 
 int /*<<< orphan*/  wakelocks_lru_most_recent (struct wakelock*) ; 

int pm_wake_lock(const char *buf)
{
	const char *str = buf;
	struct wakelock *wl;
	u64 timeout_ns = 0;
	size_t len;
	int ret = 0;

	if (!capable(CAP_BLOCK_SUSPEND))
		return -EPERM;

	while (*str && !isspace(*str))
		str++;

	len = str - buf;
	if (!len)
		return -EINVAL;

	if (*str && *str != '\n') {
		/* Find out if there's a valid timeout string appended. */
		ret = kstrtou64(skip_spaces(str), 10, &timeout_ns);
		if (ret)
			return -EINVAL;
	}

	mutex_lock(&wakelocks_lock);

	wl = wakelock_lookup_add(buf, len, true);
	if (IS_ERR(wl)) {
		ret = PTR_ERR(wl);
		goto out;
	}
	if (timeout_ns) {
		u64 timeout_ms = timeout_ns + NSEC_PER_MSEC - 1;

		do_div(timeout_ms, NSEC_PER_MSEC);
		__pm_wakeup_event(wl->ws, timeout_ms);
	} else {
		__pm_stay_awake(wl->ws);
	}

	wakelocks_lru_most_recent(wl);

 out:
	mutex_unlock(&wakelocks_lock);
	return ret;
}