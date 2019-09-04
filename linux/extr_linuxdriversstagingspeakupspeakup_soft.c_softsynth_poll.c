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
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
typedef  int __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  spinlock; scalar_t__ flushing; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  speakup_event ; 
 TYPE_1__ speakup_info ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synth_buffer_empty () ; 
 int /*<<< orphan*/ * synth_current () ; 
 int /*<<< orphan*/  synth_soft ; 

__attribute__((used)) static __poll_t softsynth_poll(struct file *fp, struct poll_table_struct *wait)
{
	unsigned long flags;
	__poll_t ret = 0;

	poll_wait(fp, &speakup_event, wait);

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	if (synth_current() == &synth_soft &&
	    (!synth_buffer_empty() || speakup_info.flushing))
		ret = EPOLLIN | EPOLLRDNORM;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	return ret;
}