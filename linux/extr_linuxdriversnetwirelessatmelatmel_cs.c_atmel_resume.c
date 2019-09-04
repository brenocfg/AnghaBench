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
struct pcmcia_device {struct local_info* priv; } ;
struct local_info {int /*<<< orphan*/  eth_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_resume(struct pcmcia_device *link)
{
	struct local_info *local = link->priv;

	atmel_open(local->eth_dev);
	netif_device_attach(local->eth_dev);

	return 0;
}