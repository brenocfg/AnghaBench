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
struct tb_switch {struct tb_switch* key; struct tb_switch* drom; struct tb_switch* ports; struct tb_switch* vendor_name; struct tb_switch* device_name; struct tb_switch* uuid; int /*<<< orphan*/  dma_port; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_port_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tb_switch*) ; 
 struct tb_switch* tb_to_switch (struct device*) ; 

__attribute__((used)) static void tb_switch_release(struct device *dev)
{
	struct tb_switch *sw = tb_to_switch(dev);

	dma_port_free(sw->dma_port);

	kfree(sw->uuid);
	kfree(sw->device_name);
	kfree(sw->vendor_name);
	kfree(sw->ports);
	kfree(sw->drom);
	kfree(sw->key);
	kfree(sw);
}