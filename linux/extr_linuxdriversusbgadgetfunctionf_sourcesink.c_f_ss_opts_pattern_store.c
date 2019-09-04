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
typedef  int u8 ;
struct f_ss_opts {int pattern; int /*<<< orphan*/  lock; scalar_t__ refcnt; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int kstrtou8 (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct f_ss_opts* to_f_ss_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t f_ss_opts_pattern_store(struct config_item *item,
				       const char *page, size_t len)
{
	struct f_ss_opts *opts = to_f_ss_opts(item);
	int ret;
	u8 num;

	mutex_lock(&opts->lock);
	if (opts->refcnt) {
		ret = -EBUSY;
		goto end;
	}

	ret = kstrtou8(page, 0, &num);
	if (ret)
		goto end;

	if (num != 0 && num != 1 && num != 2) {
		ret = -EINVAL;
		goto end;
	}

	opts->pattern = num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	return ret;
}