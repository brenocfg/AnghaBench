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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 size_t OCFS2_STACK_LABEL_LEN ; 
 scalar_t__ active_stack ; 
 int /*<<< orphan*/  cluster_stack_name ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  ocfs2_stack_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 size_t strnlen (char const*,size_t) ; 

__attribute__((used)) static ssize_t ocfs2_cluster_stack_store(struct kobject *kobj,
					 struct kobj_attribute *attr,
					 const char *buf, size_t count)
{
	size_t len = count;
	ssize_t ret;

	if (len == 0)
		return len;

	if (buf[len - 1] == '\n')
		len--;

	if ((len != OCFS2_STACK_LABEL_LEN) ||
	    (strnlen(buf, len) != len))
		return -EINVAL;

	spin_lock(&ocfs2_stack_lock);
	if (active_stack) {
		if (!strncmp(buf, cluster_stack_name, len))
			ret = count;
		else
			ret = -EBUSY;
	} else {
		memcpy(cluster_stack_name, buf, len);
		ret = count;
	}
	spin_unlock(&ocfs2_stack_lock);

	return ret;
}