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
struct tty_struct {struct tty_port* port; } ;
struct tty_bufhead {int /*<<< orphan*/  lock; int /*<<< orphan*/  priority; struct tty_buffer* head; } ;
struct tty_port {struct tty_bufhead buf; } ;
struct tty_ldisc {TYPE_1__* ops; } ;
struct tty_buffer {int /*<<< orphan*/  commit; int /*<<< orphan*/  read; int /*<<< orphan*/  next; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_buffer ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tty_buffer* smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_buffer_free (struct tty_port*,struct tty_buffer*) ; 

void tty_buffer_flush(struct tty_struct *tty, struct tty_ldisc *ld)
{
	struct tty_port *port = tty->port;
	struct tty_bufhead *buf = &port->buf;
	struct tty_buffer *next;

	atomic_inc(&buf->priority);

	mutex_lock(&buf->lock);
	/* paired w/ release in __tty_buffer_request_room; ensures there are
	 * no pending memory accesses to the freed buffer
	 */
	while ((next = smp_load_acquire(&buf->head->next)) != NULL) {
		tty_buffer_free(port, buf->head);
		buf->head = next;
	}
	buf->head->read = buf->head->commit;

	if (ld && ld->ops->flush_buffer)
		ld->ops->flush_buffer(tty);

	atomic_dec(&buf->priority);
	mutex_unlock(&buf->lock);
}