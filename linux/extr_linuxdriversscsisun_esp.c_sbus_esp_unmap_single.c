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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct esp {struct platform_device* dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static void sbus_esp_unmap_single(struct esp *esp, dma_addr_t addr,
				  size_t sz, int dir)
{
	struct platform_device *op = esp->dev;

	dma_unmap_single(&op->dev, addr, sz, dir);
}