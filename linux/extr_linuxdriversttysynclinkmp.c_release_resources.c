#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int irq_requested; int shared_mem_requested; int phys_memory_base; int lcr_mem_requested; int phys_lcr_base; int lcr_offset; int sca_base_requested; int phys_sca_base; int sca_offset; int sca_statctrl_requested; int phys_statctrl_base; int statctrl_offset; int /*<<< orphan*/  device_name; int /*<<< orphan*/ * lcr_base; int /*<<< orphan*/ * statctrl_base; int /*<<< orphan*/ * sca_base; int /*<<< orphan*/ * memory_base; int /*<<< orphan*/  irq_level; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int SCA_BASE_SIZE ; 
 int SCA_MEM_SIZE ; 
 int SCA_REG_SIZE ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int,int) ; 

__attribute__((used)) static void release_resources(SLMP_INFO *info)
{
	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):%s release_resources() entry\n",
			__FILE__,__LINE__,info->device_name );

	if ( info->irq_requested ) {
		free_irq(info->irq_level, info);
		info->irq_requested = false;
	}

	if ( info->shared_mem_requested ) {
		release_mem_region(info->phys_memory_base,SCA_MEM_SIZE);
		info->shared_mem_requested = false;
	}
	if ( info->lcr_mem_requested ) {
		release_mem_region(info->phys_lcr_base + info->lcr_offset,128);
		info->lcr_mem_requested = false;
	}
	if ( info->sca_base_requested ) {
		release_mem_region(info->phys_sca_base + info->sca_offset,SCA_BASE_SIZE);
		info->sca_base_requested = false;
	}
	if ( info->sca_statctrl_requested ) {
		release_mem_region(info->phys_statctrl_base + info->statctrl_offset,SCA_REG_SIZE);
		info->sca_statctrl_requested = false;
	}

	if (info->memory_base){
		iounmap(info->memory_base);
		info->memory_base = NULL;
	}

	if (info->sca_base) {
		iounmap(info->sca_base - info->sca_offset);
		info->sca_base=NULL;
	}

	if (info->statctrl_base) {
		iounmap(info->statctrl_base - info->statctrl_offset);
		info->statctrl_base=NULL;
	}

	if (info->lcr_base){
		iounmap(info->lcr_base - info->lcr_offset);
		info->lcr_base = NULL;
	}

	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):%s release_resources() exit\n",
			__FILE__,__LINE__,info->device_name );
}