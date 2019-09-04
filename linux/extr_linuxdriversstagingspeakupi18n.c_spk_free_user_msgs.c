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
typedef  enum msg_index_t { ____Placeholder_msg_index_t } msg_index_t ;
struct TYPE_2__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int MSG_FIRST_INDEX ; 
 int MSG_LAST_INDEX ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__* speakup_default_msgs ; 
 TYPE_1__ speakup_info ; 
 scalar_t__* speakup_msgs ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void spk_free_user_msgs(void)
{
	enum msg_index_t index;
	unsigned long flags;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	for (index = MSG_FIRST_INDEX; index < MSG_LAST_INDEX; index++) {
		if (speakup_msgs[index] != speakup_default_msgs[index]) {
			kfree(speakup_msgs[index]);
			speakup_msgs[index] = speakup_default_msgs[index];
		}
	}
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
}