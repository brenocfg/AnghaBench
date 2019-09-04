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
struct tty_bufhead {int /*<<< orphan*/  free; int /*<<< orphan*/  mem_used; } ;
struct tty_port {struct tty_bufhead buf; } ;
struct tty_buffer {scalar_t__ size; int /*<<< orphan*/  free; } ;

/* Variables and functions */
 scalar_t__ MIN_TTYB_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_sub_return (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tty_buffer*) ; 
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tty_buffer_free(struct tty_port *port, struct tty_buffer *b)
{
	struct tty_bufhead *buf = &port->buf;

	/* Dumb strategy for now - should keep some stats */
	WARN_ON(atomic_sub_return(b->size, &buf->mem_used) < 0);

	if (b->size > MIN_TTYB_SIZE)
		kfree(b);
	else if (b->size > 0)
		llist_add(&b->free, &buf->free);
}