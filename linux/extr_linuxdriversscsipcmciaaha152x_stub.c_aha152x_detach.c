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
struct pcmcia_device {int /*<<< orphan*/  priv; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  aha152x_release_cs (struct pcmcia_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aha152x_detach(struct pcmcia_device *link)
{
    dev_dbg(&link->dev, "aha152x_detach\n");

    aha152x_release_cs(link);

    /* Unlink device structure, free bits */
    kfree(link->priv);
}