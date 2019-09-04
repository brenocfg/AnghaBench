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
struct pcmcia_socket {int /*<<< orphan*/  skt_mutex; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct class_interface {int dummy; } ;

/* Variables and functions */
 struct pcmcia_socket* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pccard_cis_attr ; 
 int /*<<< orphan*/  pccard_register_pcmcia (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_card_remove (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_put_socket (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  release_cis_mem (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcmcia_bus_remove_socket(struct device *dev,
				     struct class_interface *class_intf)
{
	struct pcmcia_socket *socket = dev_get_drvdata(dev);

	if (!socket)
		return;

	pccard_register_pcmcia(socket, NULL);

	/* unregister any unbound devices */
	mutex_lock(&socket->skt_mutex);
	pcmcia_card_remove(socket, NULL);
	release_cis_mem(socket);
	mutex_unlock(&socket->skt_mutex);

	sysfs_remove_bin_file(&dev->kobj, &pccard_cis_attr);

	pcmcia_put_socket(socket);

	return;
}