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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct channel_path {int /*<<< orphan*/  lock; int /*<<< orphan*/  chpid; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int s390_vary_chpid (int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 struct channel_path* to_channelpath (struct device*) ; 

__attribute__((used)) static ssize_t chp_status_write(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct channel_path *cp = to_channelpath(dev);
	char cmd[10];
	int num_args;
	int error;

	num_args = sscanf(buf, "%5s", cmd);
	if (!num_args)
		return count;

	if (!strncasecmp(cmd, "on", 2) || !strcmp(cmd, "1")) {
		mutex_lock(&cp->lock);
		error = s390_vary_chpid(cp->chpid, 1);
		mutex_unlock(&cp->lock);
	} else if (!strncasecmp(cmd, "off", 3) || !strcmp(cmd, "0")) {
		mutex_lock(&cp->lock);
		error = s390_vary_chpid(cp->chpid, 0);
		mutex_unlock(&cp->lock);
	} else
		error = -EINVAL;

	return error < 0 ? error : count;
}