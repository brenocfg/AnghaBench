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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct kgdb_nmi_tty_priv {int /*<<< orphan*/  port; int /*<<< orphan*/  fifo; TYPE_1__ timer; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct kgdb_nmi_tty_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfifo_len (int /*<<< orphan*/ *) ; 
 scalar_t__ kfifo_out (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kgdb_nmi_num_readers ; 
 scalar_t__ likely (int) ; 
 struct kgdb_nmi_tty_priv* priv ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kgdb_nmi_tty_receiver(struct timer_list *t)
{
	struct kgdb_nmi_tty_priv *priv = from_timer(priv, t, timer);
	char ch;

	priv->timer.expires = jiffies + (HZ/100);
	add_timer(&priv->timer);

	if (likely(!atomic_read(&kgdb_nmi_num_readers) ||
		   !kfifo_len(&priv->fifo)))
		return;

	while (kfifo_out(&priv->fifo, &ch, 1))
		tty_insert_flip_char(&priv->port, ch, TTY_NORMAL);
	tty_flip_buffer_push(&priv->port);
}