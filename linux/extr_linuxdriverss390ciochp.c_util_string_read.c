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
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  util_str; } ;
struct channel_path {int /*<<< orphan*/  lock; TYPE_1__ desc_fmt3; } ;
struct bin_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  memory_read_from_buffer (char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct channel_path* to_channelpath (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t util_string_read(struct file *filp, struct kobject *kobj,
				struct bin_attribute *attr, char *buf,
				loff_t off, size_t count)
{
	struct channel_path *chp = to_channelpath(kobj_to_dev(kobj));
	ssize_t rc;

	mutex_lock(&chp->lock);
	rc = memory_read_from_buffer(buf, count, &off, chp->desc_fmt3.util_str,
				     sizeof(chp->desc_fmt3.util_str));
	mutex_unlock(&chp->lock);

	return rc;
}