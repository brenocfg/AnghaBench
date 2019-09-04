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
struct sclp_buffer {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sclp_emit_buffer (struct sclp_buffer*,int /*<<< orphan*/  (*) (struct sclp_buffer*,int)) ; 
 int /*<<< orphan*/  sclp_tty_buffer_count ; 
 int /*<<< orphan*/  sclp_tty_lock ; 
 int /*<<< orphan*/  sclp_tty_outqueue ; 
 int /*<<< orphan*/  sclp_ttybuf_callback (struct sclp_buffer*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void
__sclp_ttybuf_emit(struct sclp_buffer *buffer)
{
	unsigned long flags;
	int count;
	int rc;

	spin_lock_irqsave(&sclp_tty_lock, flags);
	list_add_tail(&buffer->list, &sclp_tty_outqueue);
	count = sclp_tty_buffer_count++;
	spin_unlock_irqrestore(&sclp_tty_lock, flags);
	if (count)
		return;
	rc = sclp_emit_buffer(buffer, sclp_ttybuf_callback);
	if (rc)
		sclp_ttybuf_callback(buffer, rc);
}