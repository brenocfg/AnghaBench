#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_7__ {scalar_t__ next; } ;
struct TYPE_6__ {scalar_t__ expires; } ;

/* Variables and functions */
 scalar_t__ BUFFER_MAX_DELAY ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_del (struct list_head*) ; 
 scalar_t__ list_empty (TYPE_3__*) ; 
 int /*<<< orphan*/  sclp_console_full ; 
 int /*<<< orphan*/  sclp_sync_wait () ; 
 int sclp_vt220_add_msg (int /*<<< orphan*/ *,unsigned char const*,int,int) ; 
 int /*<<< orphan*/ * sclp_vt220_current_request ; 
 scalar_t__ sclp_vt220_drop_buffer () ; 
 int /*<<< orphan*/  sclp_vt220_emit_current () ; 
 TYPE_3__ sclp_vt220_empty ; 
 int /*<<< orphan*/ * sclp_vt220_initialize_page (void*) ; 
 int /*<<< orphan*/  sclp_vt220_lock ; 
 scalar_t__ sclp_vt220_suspended ; 
 TYPE_1__ sclp_vt220_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

__attribute__((used)) static int
__sclp_vt220_write(const unsigned char *buf, int count, int do_schedule,
		   int convertlf, int may_fail)
{
	unsigned long flags;
	void *page;
	int written;
	int overall_written;

	if (count <= 0)
		return 0;
	overall_written = 0;
	spin_lock_irqsave(&sclp_vt220_lock, flags);
	do {
		/* Create an sclp output buffer if none exists yet */
		if (sclp_vt220_current_request == NULL) {
			if (list_empty(&sclp_vt220_empty))
				sclp_console_full++;
			while (list_empty(&sclp_vt220_empty)) {
				if (may_fail || sclp_vt220_suspended)
					goto out;
				if (sclp_vt220_drop_buffer())
					break;
				spin_unlock_irqrestore(&sclp_vt220_lock, flags);

				sclp_sync_wait();
				spin_lock_irqsave(&sclp_vt220_lock, flags);
			}
			page = (void *) sclp_vt220_empty.next;
			list_del((struct list_head *) page);
			sclp_vt220_current_request =
				sclp_vt220_initialize_page(page);
		}
		/* Try to write the string to the current request buffer */
		written = sclp_vt220_add_msg(sclp_vt220_current_request,
					     buf, count, convertlf);
		overall_written += written;
		if (written == count)
			break;
		/*
		 * Not all characters could be written to the current
		 * output buffer. Emit the buffer, create a new buffer
		 * and then output the rest of the string.
		 */
		spin_unlock_irqrestore(&sclp_vt220_lock, flags);
		sclp_vt220_emit_current();
		spin_lock_irqsave(&sclp_vt220_lock, flags);
		buf += written;
		count -= written;
	} while (count > 0);
	/* Setup timer to output current console buffer after some time */
	if (sclp_vt220_current_request != NULL &&
	    !timer_pending(&sclp_vt220_timer) && do_schedule) {
		sclp_vt220_timer.expires = jiffies + BUFFER_MAX_DELAY;
		add_timer(&sclp_vt220_timer);
	}
out:
	spin_unlock_irqrestore(&sclp_vt220_lock, flags);
	return overall_written;
}