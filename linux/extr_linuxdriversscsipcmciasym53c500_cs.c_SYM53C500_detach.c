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
struct pcmcia_device {int /*<<< orphan*/ * priv; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYM53C500_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
SYM53C500_detach(struct pcmcia_device *link)
{
	dev_dbg(&link->dev, "SYM53C500_detach\n");

	SYM53C500_release(link);

	kfree(link->priv);
	link->priv = NULL;
}