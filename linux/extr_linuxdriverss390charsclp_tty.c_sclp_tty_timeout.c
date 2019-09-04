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
struct timer_list {int dummy; } ;
struct sclp_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sclp_ttybuf_emit (struct sclp_buffer*) ; 
 int /*<<< orphan*/  sclp_tty_lock ; 
 struct sclp_buffer* sclp_ttybuf ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
sclp_tty_timeout(struct timer_list *unused)
{
	unsigned long flags;
	struct sclp_buffer *buf;

	spin_lock_irqsave(&sclp_tty_lock, flags);
	buf = sclp_ttybuf;
	sclp_ttybuf = NULL;
	spin_unlock_irqrestore(&sclp_tty_lock, flags);

	if (buf != NULL) {
		__sclp_ttybuf_emit(buf);
	}
}