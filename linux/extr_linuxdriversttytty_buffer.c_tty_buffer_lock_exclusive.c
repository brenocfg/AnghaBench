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
struct tty_bufhead {int /*<<< orphan*/  lock; int /*<<< orphan*/  priority; } ;
struct tty_port {struct tty_bufhead buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

void tty_buffer_lock_exclusive(struct tty_port *port)
{
	struct tty_bufhead *buf = &port->buf;

	atomic_inc(&buf->priority);
	mutex_lock(&buf->lock);
}