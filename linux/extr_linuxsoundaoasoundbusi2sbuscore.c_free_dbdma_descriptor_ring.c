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
struct i2sbus_dev {int /*<<< orphan*/  macio; } ;
struct dbdma_command_mem {int /*<<< orphan*/  bus_addr; int /*<<< orphan*/  space; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* macio_get_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_dbdma_descriptor_ring(struct i2sbus_dev *i2sdev,
				       struct dbdma_command_mem *r)
{
	if (!r->space) return;

	dma_free_coherent(&macio_get_pci_dev(i2sdev->macio)->dev,
			    r->size, r->space, r->bus_addr);
}