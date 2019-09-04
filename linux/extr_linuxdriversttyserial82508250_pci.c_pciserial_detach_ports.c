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
struct serial_private {int nr; int /*<<< orphan*/  dev; int /*<<< orphan*/ * line; } ;
struct pci_serial_quirk {int /*<<< orphan*/  (* exit ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct pci_serial_quirk* find_quirk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial8250_unregister_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pciserial_detach_ports(struct serial_private *priv)
{
	struct pci_serial_quirk *quirk;
	int i;

	for (i = 0; i < priv->nr; i++)
		serial8250_unregister_port(priv->line[i]);

	/*
	 * Find the exit quirks.
	 */
	quirk = find_quirk(priv->dev);
	if (quirk->exit)
		quirk->exit(priv->dev);
}