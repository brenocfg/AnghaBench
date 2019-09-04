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
struct kobj_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int pv_major; int pv_minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__ locking_max_version ; 
 int /*<<< orphan*/  ocfs2_stack_lock ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t ocfs2_max_locking_protocol_show(struct kobject *kobj,
					       struct kobj_attribute *attr,
					       char *buf)
{
	ssize_t ret = 0;

	spin_lock(&ocfs2_stack_lock);
	if (locking_max_version.pv_major)
		ret = snprintf(buf, PAGE_SIZE, "%u.%u\n",
			       locking_max_version.pv_major,
			       locking_max_version.pv_minor);
	spin_unlock(&ocfs2_stack_lock);

	return ret;
}