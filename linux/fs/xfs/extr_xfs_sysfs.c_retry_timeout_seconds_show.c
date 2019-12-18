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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int MSEC_PER_SEC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ XFS_ERR_RETRY_FOREVER ; 
 int jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct xfs_error_cfg* to_error_cfg (struct kobject*) ; 

__attribute__((used)) static ssize_t
retry_timeout_seconds_show(
	struct kobject	*kobject,
	char		*buf)
{
	int		timeout;
	struct xfs_error_cfg *cfg = to_error_cfg(kobject);

	if (cfg->retry_timeout == XFS_ERR_RETRY_FOREVER)
		timeout = -1;
	else
		timeout = jiffies_to_msecs(cfg->retry_timeout) / MSEC_PER_SEC;

	return snprintf(buf, PAGE_SIZE, "%d\n", timeout);
}