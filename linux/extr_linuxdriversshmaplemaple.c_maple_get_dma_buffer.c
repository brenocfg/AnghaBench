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

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  MAPLE_DMA_PAGES ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 void* maple_sendbuf ; 

__attribute__((used)) static int maple_get_dma_buffer(void)
{
	maple_sendbuf =
	    (void *) __get_free_pages(GFP_KERNEL | __GFP_ZERO,
				      MAPLE_DMA_PAGES);
	if (!maple_sendbuf)
		return -ENOMEM;
	return 0;
}