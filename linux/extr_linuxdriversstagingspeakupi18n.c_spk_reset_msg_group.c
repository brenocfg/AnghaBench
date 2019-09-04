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
struct msg_group_t {int start; int end; } ;
typedef  enum msg_index_t { ____Placeholder_msg_index_t } msg_index_t ;
struct TYPE_2__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__* speakup_default_msgs ; 
 TYPE_1__ speakup_info ; 
 scalar_t__* speakup_msgs ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void spk_reset_msg_group(struct msg_group_t *group)
{
	unsigned long flags;
	enum msg_index_t i;

	spin_lock_irqsave(&speakup_info.spinlock, flags);

	for (i = group->start; i <= group->end; i++) {
		if (speakup_msgs[i] != speakup_default_msgs[i])
			kfree(speakup_msgs[i]);
		speakup_msgs[i] = speakup_default_msgs[i];
	}
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
}