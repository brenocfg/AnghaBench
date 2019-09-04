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
struct esp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int) ; 

__attribute__((used)) static int jazz_esp_map_sg(struct esp *esp, struct scatterlist *sg,
				  int num_sg, int dir)
{
	return dma_map_sg(esp->dev, sg, num_sg, dir);
}