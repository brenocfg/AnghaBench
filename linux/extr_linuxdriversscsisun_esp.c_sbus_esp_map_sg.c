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
struct scatterlist {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct esp {struct platform_device* dev; } ;

/* Variables and functions */
 int dma_map_sg (int /*<<< orphan*/ *,struct scatterlist*,int,int) ; 

__attribute__((used)) static int sbus_esp_map_sg(struct esp *esp, struct scatterlist *sg,
				  int num_sg, int dir)
{
	struct platform_device *op = esp->dev;

	return dma_map_sg(&op->dev, sg, num_sg, dir);
}