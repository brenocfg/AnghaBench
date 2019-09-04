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
struct pcmcia_device {struct ipw_dev* priv; } ;
struct ipw_dev {int /*<<< orphan*/ * hardware; int /*<<< orphan*/ * network; int /*<<< orphan*/ * tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipwireless_hardware_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipwireless_network_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipwireless_tty_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ipw_dev*) ; 
 int /*<<< orphan*/  release_ipwireless (struct ipw_dev*) ; 

__attribute__((used)) static void ipwireless_detach(struct pcmcia_device *link)
{
	struct ipw_dev *ipw = link->priv;

	release_ipwireless(ipw);

	if (ipw->tty != NULL)
		ipwireless_tty_free(ipw->tty);
	if (ipw->network != NULL)
		ipwireless_network_free(ipw->network);
	if (ipw->hardware != NULL)
		ipwireless_hardware_free(ipw->hardware);
	kfree(ipw);
}