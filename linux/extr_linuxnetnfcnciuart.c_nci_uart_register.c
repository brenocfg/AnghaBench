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
struct TYPE_2__ {scalar_t__ recv; scalar_t__ recv_buf; int /*<<< orphan*/  send; int /*<<< orphan*/  close; int /*<<< orphan*/  open; } ;
struct nci_uart {size_t driver; int /*<<< orphan*/  name; TYPE_1__ ops; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ nci_uart_default_recv ; 
 scalar_t__ nci_uart_default_recv_buf ; 
 struct nci_uart** nci_uart_drivers ; 
 int /*<<< orphan*/  nci_uart_send ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,size_t) ; 

int nci_uart_register(struct nci_uart *nu)
{
	if (!nu || !nu->ops.open ||
	    !nu->ops.recv || !nu->ops.close)
		return -EINVAL;

	/* Set the send callback */
	nu->ops.send = nci_uart_send;

	/* Install default handlers if not overridden */
	if (!nu->ops.recv_buf)
		nu->ops.recv_buf = nci_uart_default_recv_buf;
	if (!nu->ops.recv)
		nu->ops.recv = nci_uart_default_recv;

	/* Add this driver in the driver list */
	if (nci_uart_drivers[nu->driver]) {
		pr_err("driver %d is already registered\n", nu->driver);
		return -EBUSY;
	}
	nci_uart_drivers[nu->driver] = nu;

	pr_info("NCI uart driver '%s [%d]' registered\n", nu->name, nu->driver);

	return 0;
}