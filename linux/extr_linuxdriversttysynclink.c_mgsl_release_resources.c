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
struct mgsl_struct {int irq_requested; int dma_requested; int io_addr_requested; int shared_mem_requested; int phys_memory_base; int lcr_mem_requested; int phys_lcr_base; int lcr_offset; int /*<<< orphan*/  device_name; int /*<<< orphan*/ * lcr_base; int /*<<< orphan*/ * memory_base; int /*<<< orphan*/  io_addr_size; int /*<<< orphan*/  io_base; int /*<<< orphan*/  dma_level; int /*<<< orphan*/  irq_level; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mgsl_struct*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgsl_free_dma_buffers (struct mgsl_struct*) ; 
 int /*<<< orphan*/  mgsl_free_intermediate_rxbuffer_memory (struct mgsl_struct*) ; 
 int /*<<< orphan*/  mgsl_free_intermediate_txbuffer_memory (struct mgsl_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int,int) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mgsl_release_resources(struct mgsl_struct *info)
{
	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):mgsl_release_resources(%s) entry\n",
			__FILE__,__LINE__,info->device_name );
			
	if ( info->irq_requested ) {
		free_irq(info->irq_level, info);
		info->irq_requested = false;
	}
	if ( info->dma_requested ) {
		disable_dma(info->dma_level);
		free_dma(info->dma_level);
		info->dma_requested = false;
	}
	mgsl_free_dma_buffers(info);
	mgsl_free_intermediate_rxbuffer_memory(info);
     	mgsl_free_intermediate_txbuffer_memory(info);
	
	if ( info->io_addr_requested ) {
		release_region(info->io_base,info->io_addr_size);
		info->io_addr_requested = false;
	}
	if ( info->shared_mem_requested ) {
		release_mem_region(info->phys_memory_base,0x40000);
		info->shared_mem_requested = false;
	}
	if ( info->lcr_mem_requested ) {
		release_mem_region(info->phys_lcr_base + info->lcr_offset,128);
		info->lcr_mem_requested = false;
	}
	if (info->memory_base){
		iounmap(info->memory_base);
		info->memory_base = NULL;
	}
	if (info->lcr_base){
		iounmap(info->lcr_base - info->lcr_offset);
		info->lcr_base = NULL;
	}
	
	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):mgsl_release_resources(%s) exit\n",
			__FILE__,__LINE__,info->device_name );
			
}