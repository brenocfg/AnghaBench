#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_mem_chunks; TYPE_2__* mem_chunks; } ;
struct ath10k {TYPE_1__ wmi; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath10k_wmi_free_host_mem(struct ath10k *ar)
{
	int i;

	/* free the host memory chunks requested by firmware */
	for (i = 0; i < ar->wmi.num_mem_chunks; i++) {
		dma_free_coherent(ar->dev,
				  ar->wmi.mem_chunks[i].len,
				  ar->wmi.mem_chunks[i].vaddr,
				  ar->wmi.mem_chunks[i].paddr);
	}

	ar->wmi.num_mem_chunks = 0;
}