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
struct xfs_error_cfg {int max_retries; } ;
struct kobject {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int XFS_ERR_RETRY_FOREVER ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct xfs_error_cfg* to_error_cfg (struct kobject*) ; 

__attribute__((used)) static ssize_t
max_retries_show(
	struct kobject	*kobject,
	char		*buf)
{
	int		retries;
	struct xfs_error_cfg *cfg = to_error_cfg(kobject);

	if (cfg->max_retries == XFS_ERR_RETRY_FOREVER)
		retries = -1;
	else
		retries = cfg->max_retries;

	return snprintf(buf, PAGE_SIZE, "%d\n", retries);
}