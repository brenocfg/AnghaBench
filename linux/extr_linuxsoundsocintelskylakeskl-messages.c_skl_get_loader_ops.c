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
struct skl_dsp_loader_ops {int /*<<< orphan*/  free_dma_buf; int /*<<< orphan*/  alloc_dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct skl_dsp_loader_ops*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skl_alloc_dma_buf ; 
 int /*<<< orphan*/  skl_free_dma_buf ; 

__attribute__((used)) static struct skl_dsp_loader_ops skl_get_loader_ops(void)
{
	struct skl_dsp_loader_ops loader_ops;

	memset(&loader_ops, 0, sizeof(struct skl_dsp_loader_ops));

	loader_ops.alloc_dma_buf = skl_alloc_dma_buf;
	loader_ops.free_dma_buf = skl_free_dma_buf;

	return loader_ops;
}