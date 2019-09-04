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
struct pcmcia_device {scalar_t__ priv; int /*<<< orphan*/  dev; } ;
struct local_info {int /*<<< orphan*/ * eth_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  airo_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  stop_airo_card (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void airo_detach(struct pcmcia_device *link)
{
	dev_dbg(&link->dev, "airo_detach\n");

	airo_release(link);

	if (((struct local_info *)link->priv)->eth_dev) {
		stop_airo_card(((struct local_info *)link->priv)->eth_dev,
			       0);
	}
	((struct local_info *)link->priv)->eth_dev = NULL;

	kfree(link->priv);
}