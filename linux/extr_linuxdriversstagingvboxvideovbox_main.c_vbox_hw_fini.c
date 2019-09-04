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
struct vbox_private {int /*<<< orphan*/  guest_heap; TYPE_1__* dev; int /*<<< orphan*/  guest_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbox_accel_fini (struct vbox_private*) ; 

__attribute__((used)) static void vbox_hw_fini(struct vbox_private *vbox)
{
	vbox_accel_fini(vbox);
	gen_pool_destroy(vbox->guest_pool);
	pci_iounmap(vbox->dev->pdev, vbox->guest_heap);
}