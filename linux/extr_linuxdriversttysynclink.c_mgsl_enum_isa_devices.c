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
struct mgsl_struct {unsigned int io_base; unsigned int irq_level; unsigned int dma_level; int io_addr_size; scalar_t__ irq_flags; int /*<<< orphan*/  bus_type; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_ERROR ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int MAX_ISA_DEVICES ; 
 int /*<<< orphan*/  MGSL_BUS_TYPE_ISA ; 
 scalar_t__ debug_level ; 
 scalar_t__* dma ; 
 scalar_t__* io ; 
 scalar_t__* irq ; 
 unsigned int irq_canonicalize (unsigned int) ; 
 int /*<<< orphan*/  mgsl_add_device (struct mgsl_struct*) ; 
 struct mgsl_struct* mgsl_allocate_device () ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void mgsl_enum_isa_devices(void)
{
	struct mgsl_struct *info;
	int i;
		
	/* Check for user specified ISA devices */
	
	for (i=0 ;(i < MAX_ISA_DEVICES) && io[i] && irq[i]; i++){
		if ( debug_level >= DEBUG_LEVEL_INFO )
			printk("ISA device specified io=%04X,irq=%d,dma=%d\n",
				io[i], irq[i], dma[i] );
		
		info = mgsl_allocate_device();
		if ( !info ) {
			/* error allocating device instance data */
			if ( debug_level >= DEBUG_LEVEL_ERROR )
				printk( "can't allocate device instance data.\n");
			continue;
		}
		
		/* Copy user configuration info to device instance data */
		info->io_base = (unsigned int)io[i];
		info->irq_level = (unsigned int)irq[i];
		info->irq_level = irq_canonicalize(info->irq_level);
		info->dma_level = (unsigned int)dma[i];
		info->bus_type = MGSL_BUS_TYPE_ISA;
		info->io_addr_size = 16;
		info->irq_flags = 0;
		
		mgsl_add_device( info );
	}
}