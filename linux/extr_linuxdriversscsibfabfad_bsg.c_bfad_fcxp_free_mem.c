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
typedef  int uint32_t ;
struct bfad_s {TYPE_1__* pcidev; } ;
struct bfad_buf_info {int /*<<< orphan*/  phys; int /*<<< orphan*/ * virt; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bfad_buf_info*) ; 

void
bfad_fcxp_free_mem(struct bfad_s *bfad, struct bfad_buf_info *buf_base,
		   uint32_t num_sgles)
{
	int i;
	struct bfad_buf_info *buf_info = buf_base;

	if (buf_base) {
		for (i = 0; i < num_sgles; buf_info++, i++) {
			if (buf_info->virt != NULL)
				dma_free_coherent(&bfad->pcidev->dev,
					buf_info->size, buf_info->virt,
					buf_info->phys);
		}
		kfree(buf_base);
	}
}