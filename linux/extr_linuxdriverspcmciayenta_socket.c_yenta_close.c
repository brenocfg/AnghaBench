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
struct yenta_socket {int /*<<< orphan*/  base; int /*<<< orphan*/  poll_timer; scalar_t__ cb_irq; int /*<<< orphan*/  socket; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB_SOCKET_MASK ; 
 int /*<<< orphan*/  I365_CSCINT ; 
 int /*<<< orphan*/  cb_writel (struct yenta_socket*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_yenta_registers ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exca_writeb (struct yenta_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct yenta_socket*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct yenta_socket*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct yenta_socket* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_unregister_socket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yenta_free_resources (struct yenta_socket*) ; 

__attribute__((used)) static void yenta_close(struct pci_dev *dev)
{
	struct yenta_socket *sock = pci_get_drvdata(dev);

	/* Remove the register attributes */
	device_remove_file(&dev->dev, &dev_attr_yenta_registers);

	/* we don't want a dying socket registered */
	pcmcia_unregister_socket(&sock->socket);

	/* Disable all events so we don't die in an IRQ storm */
	cb_writel(sock, CB_SOCKET_MASK, 0x0);
	exca_writeb(sock, I365_CSCINT, 0);

	if (sock->cb_irq)
		free_irq(sock->cb_irq, sock);
	else
		del_timer_sync(&sock->poll_timer);

	iounmap(sock->base);
	yenta_free_resources(sock);

	pci_release_regions(dev);
	pci_disable_device(dev);
	pci_set_drvdata(dev, NULL);
	kfree(sock);
}