#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HP_FIRST_WORD ; 
 int HP_NUM_WORDS ; 
 int /*<<< orphan*/ * PTR_ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __frame_ptr ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_lfsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_dma ; 
 int /*<<< orphan*/ * frame_ptr ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* pcfg ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  qman_dma_portal ; 
 TYPE_1__* qman_get_qm_portal_config (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allocate_frame_data(void)
{
	u32 lfsr = HP_FIRST_WORD;
	int loop;

	if (!qman_dma_portal) {
		pr_crit("portal not available\n");
		return -EIO;
	}

	pcfg = qman_get_qm_portal_config(qman_dma_portal);

	__frame_ptr = kmalloc(4 * HP_NUM_WORDS, GFP_KERNEL);
	if (!__frame_ptr)
		return -ENOMEM;

	frame_ptr = PTR_ALIGN(__frame_ptr, 64);
	for (loop = 0; loop < HP_NUM_WORDS; loop++) {
		frame_ptr[loop] = lfsr;
		lfsr = do_lfsr(lfsr);
	}

	frame_dma = dma_map_single(pcfg->dev, frame_ptr, 4 * HP_NUM_WORDS,
				   DMA_BIDIRECTIONAL);
	if (dma_mapping_error(pcfg->dev, frame_dma)) {
		pr_crit("dma mapping failure\n");
		kfree(__frame_ptr);
		return -EIO;
	}

	return 0;
}