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
struct mgsl_struct {int /*<<< orphan*/  device_name; scalar_t__ dma_level; int /*<<< orphan*/  init_error; scalar_t__ irq_level; scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int /*<<< orphan*/  DiagStatus_AddressFailure ; 
 int /*<<< orphan*/  DiagStatus_DmaFailure ; 
 int /*<<< orphan*/  DiagStatus_IrqFailure ; 
 int ENODEV ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  mgsl_dma_test (struct mgsl_struct*) ; 
 int /*<<< orphan*/  mgsl_irq_test (struct mgsl_struct*) ; 
 int /*<<< orphan*/  mgsl_register_test (struct mgsl_struct*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int mgsl_adapter_test( struct mgsl_struct *info )
{
	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):Testing device %s\n",
			__FILE__,__LINE__,info->device_name );
			
	if ( !mgsl_register_test( info ) ) {
		info->init_error = DiagStatus_AddressFailure;
		printk( "%s(%d):Register test failure for device %s Addr=%04X\n",
			__FILE__,__LINE__,info->device_name, (unsigned short)(info->io_base) );
		return -ENODEV;
	}

	if ( !mgsl_irq_test( info ) ) {
		info->init_error = DiagStatus_IrqFailure;
		printk( "%s(%d):Interrupt test failure for device %s IRQ=%d\n",
			__FILE__,__LINE__,info->device_name, (unsigned short)(info->irq_level) );
		return -ENODEV;
	}

	if ( !mgsl_dma_test( info ) ) {
		info->init_error = DiagStatus_DmaFailure;
		printk( "%s(%d):DMA test failure for device %s DMA=%d\n",
			__FILE__,__LINE__,info->device_name, (unsigned short)(info->dma_level) );
		return -ENODEV;
	}

	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):device %s passed diagnostics\n",
			__FILE__,__LINE__,info->device_name );
			
	return 0;

}