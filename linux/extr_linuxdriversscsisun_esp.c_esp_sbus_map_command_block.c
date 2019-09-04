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
struct esp {int /*<<< orphan*/  command_block; int /*<<< orphan*/  command_block_dma; struct platform_device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp_sbus_map_command_block(struct esp *esp)
{
	struct platform_device *op = esp->dev;

	esp->command_block = dma_alloc_coherent(&op->dev, 16,
						&esp->command_block_dma,
						GFP_ATOMIC);
	if (!esp->command_block)
		return -ENOMEM;
	return 0;
}