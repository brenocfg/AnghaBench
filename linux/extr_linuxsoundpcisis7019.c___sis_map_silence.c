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
struct sis7019 {int /*<<< orphan*/  silence_users; int /*<<< orphan*/ * suspend_state; TYPE_1__* pci; int /*<<< orphan*/  silence_dma_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __sis_map_silence(struct sis7019 *sis)
{
	/* Helper function: must hold sis->voice_lock on entry */
	if (!sis->silence_users)
		sis->silence_dma_addr = dma_map_single(&sis->pci->dev,
						sis->suspend_state[0],
						4096, DMA_TO_DEVICE);
	sis->silence_users++;
}