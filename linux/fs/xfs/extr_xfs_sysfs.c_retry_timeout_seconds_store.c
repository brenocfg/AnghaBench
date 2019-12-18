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
struct xfs_error_cfg {scalar_t__ retry_timeout; } ;
struct kobject {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EINVAL ; 
 scalar_t__ LONG_MAX ; 
 int MSEC_PER_SEC ; 
 scalar_t__ XFS_ERR_RETRY_FOREVER ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct xfs_error_cfg* to_error_cfg (struct kobject*) ; 

__attribute__((used)) static ssize_t
retry_timeout_seconds_store(
	struct kobject	*kobject,
	const char	*buf,
	size_t		count)
{
	struct xfs_error_cfg *cfg = to_error_cfg(kobject);
	int		ret;
	int		val;

	ret = kstrtoint(buf, 0, &val);
	if (ret)
		return ret;

	/* 1 day timeout maximum, -1 means infinite */
	if (val < -1 || val > 86400)
		return -EINVAL;

	if (val == -1)
		cfg->retry_timeout = XFS_ERR_RETRY_FOREVER;
	else {
		cfg->retry_timeout = msecs_to_jiffies(val * MSEC_PER_SEC);
		ASSERT(msecs_to_jiffies(val * MSEC_PER_SEC) < LONG_MAX);
	}
	return count;
}