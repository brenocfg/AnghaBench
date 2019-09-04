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
struct sk_buff {scalar_t__ sk; } ;
struct rfcomm_dev {int /*<<< orphan*/  port; int /*<<< orphan*/  flags; int /*<<< orphan*/  wmem_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFCOMM_TTY_ATTACHED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rfcomm_wfree(struct sk_buff *skb)
{
	struct rfcomm_dev *dev = (void *) skb->sk;
	atomic_dec(&dev->wmem_alloc);
	if (test_bit(RFCOMM_TTY_ATTACHED, &dev->flags))
		tty_port_tty_wakeup(&dev->port);
	tty_port_put(&dev->port);
}