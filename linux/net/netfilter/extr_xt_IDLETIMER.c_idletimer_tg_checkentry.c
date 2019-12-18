#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xt_tgchk_param {struct idletimer_tg_info* targinfo; } ;
struct idletimer_tg_info {char* label; int timeout; TYPE_1__* timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int EINVAL ; 
 int INT_MAX ; 
 scalar_t__ MAX_IDLETIMER_LABEL_SIZE ; 
 TYPE_1__* __idletimer_tg_find_by_label (char*) ; 
 int idletimer_tg_create (struct idletimer_tg_info*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_mutex ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 scalar_t__ strnlen (char*,scalar_t__) ; 

__attribute__((used)) static int idletimer_tg_checkentry(const struct xt_tgchk_param *par)
{
	struct idletimer_tg_info *info = par->targinfo;
	int ret;

	pr_debug("checkentry targinfo%s\n", info->label);

	if (info->timeout == 0) {
		pr_debug("timeout value is zero\n");
		return -EINVAL;
	}
	if (info->timeout >= INT_MAX / 1000) {
		pr_debug("timeout value is too big\n");
		return -EINVAL;
	}
	if (info->label[0] == '\0' ||
	    strnlen(info->label,
		    MAX_IDLETIMER_LABEL_SIZE) == MAX_IDLETIMER_LABEL_SIZE) {
		pr_debug("label is empty or not nul-terminated\n");
		return -EINVAL;
	}

	mutex_lock(&list_mutex);

	info->timer = __idletimer_tg_find_by_label(info->label);
	if (info->timer) {
		info->timer->refcnt++;
		mod_timer(&info->timer->timer,
			  msecs_to_jiffies(info->timeout * 1000) + jiffies);

		pr_debug("increased refcnt of timer %s to %u\n",
			 info->label, info->timer->refcnt);
	} else {
		ret = idletimer_tg_create(info);
		if (ret < 0) {
			pr_debug("failed to create timer\n");
			mutex_unlock(&list_mutex);
			return ret;
		}
	}

	mutex_unlock(&list_mutex);
	return 0;
}