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
typedef  scalar_t__ u32 ;
struct scatterlist {scalar_t__ dma_address; } ;
struct esp {int dummy; } ;

/* Variables and functions */
 scalar_t__ sg_virt (struct scatterlist*) ; 

__attribute__((used)) static int mac_esp_map_sg(struct esp *esp, struct scatterlist *sg,
			  int num_sg, int dir)
{
	int i;

	for (i = 0; i < num_sg; i++)
		sg[i].dma_address = (u32)sg_virt(&sg[i]);
	return num_sg;
}