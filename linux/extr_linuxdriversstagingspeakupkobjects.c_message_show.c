#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msg_group_t {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct kobject {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct kobj_attribute {TYPE_1__ attr; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  message_show_helper (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ speakup_info ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct msg_group_t* spk_find_msg_group (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t message_show(struct kobject *kobj,
			    struct kobj_attribute *attr, char *buf)
{
	ssize_t retval = 0;
	struct msg_group_t *group = spk_find_msg_group(attr->attr.name);
	unsigned long flags;

	if (WARN_ON(!group))
		return -EINVAL;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	retval = message_show_helper(buf, group->start, group->end);
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	return retval;
}