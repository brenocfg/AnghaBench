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
typedef  int /*<<< orphan*/  u32 ;
struct mbo {int /*<<< orphan*/  bus_address; int /*<<< orphan*/  virt_address; TYPE_1__* ifp; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* driver_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_free(struct mbo *mbo, u32 size)
{
	struct device *dev = mbo->ifp->driver_dev;

	dma_free_coherent(dev, size, mbo->virt_address, mbo->bus_address);
}