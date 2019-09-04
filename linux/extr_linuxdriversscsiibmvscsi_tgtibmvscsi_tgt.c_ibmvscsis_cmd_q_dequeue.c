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
typedef  int uint ;
struct viosrp_crq {scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_rmb () ; 

__attribute__((used)) static struct viosrp_crq *ibmvscsis_cmd_q_dequeue(uint mask,
						  uint *current_index,
						  struct viosrp_crq *base_addr)
{
	struct viosrp_crq *ptr;

	ptr = base_addr + *current_index;

	if (ptr->valid) {
		*current_index = (*current_index + 1) & mask;
		dma_rmb();
	} else {
		ptr = NULL;
	}

	return ptr;
}