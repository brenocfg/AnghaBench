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
typedef  int /*<<< orphan*/  u8 ;
struct tty_struct {scalar_t__ disc_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* recv_buf ) (struct nci_uart*,void*,char*,int) ;} ;
struct nci_uart {int /*<<< orphan*/  rx_lock; TYPE_1__ ops; struct tty_struct* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nci_uart*,void*,char*,int) ; 
 int /*<<< orphan*/  tty_unthrottle (struct tty_struct*) ; 

__attribute__((used)) static void nci_uart_tty_receive(struct tty_struct *tty, const u8 *data,
				 char *flags, int count)
{
	struct nci_uart *nu = (void *)tty->disc_data;

	if (!nu || tty != nu->tty)
		return;

	spin_lock(&nu->rx_lock);
	nu->ops.recv_buf(nu, (void *)data, flags, count);
	spin_unlock(&nu->rx_lock);

	tty_unthrottle(tty);
}