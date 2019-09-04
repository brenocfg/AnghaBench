#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int port_count; scalar_t__ init_error; } ;
struct TYPE_7__ {int port_count; TYPE_2__** port_array; int /*<<< orphan*/  device_name; scalar_t__ irq_level; scalar_t__ phys_sca_base; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int ENODEV ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  init_adapter (TYPE_1__*) ; 
 int /*<<< orphan*/  irq_test (TYPE_2__*) ; 
 int /*<<< orphan*/  loopback_test (TYPE_2__*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ register_test (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int adapter_test( SLMP_INFO *info )
{
	unsigned long flags;
	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):Testing device %s\n",
			__FILE__,__LINE__,info->device_name );

	spin_lock_irqsave(&info->lock,flags);
	init_adapter(info);
	spin_unlock_irqrestore(&info->lock,flags);

	info->port_array[0]->port_count = 0;

	if ( register_test(info->port_array[0]) &&
		register_test(info->port_array[1])) {

		info->port_array[0]->port_count = 2;

		if ( register_test(info->port_array[2]) &&
			register_test(info->port_array[3]) )
			info->port_array[0]->port_count += 2;
	}
	else {
		printk( "%s(%d):Register test failure for device %s Addr=%08lX\n",
			__FILE__,__LINE__,info->device_name, (unsigned long)(info->phys_sca_base));
		return -ENODEV;
	}

	if ( !irq_test(info->port_array[0]) ||
		!irq_test(info->port_array[1]) ||
		 (info->port_count == 4 && !irq_test(info->port_array[2])) ||
		 (info->port_count == 4 && !irq_test(info->port_array[3]))) {
		printk( "%s(%d):Interrupt test failure for device %s IRQ=%d\n",
			__FILE__,__LINE__,info->device_name, (unsigned short)(info->irq_level) );
		return -ENODEV;
	}

	if (!loopback_test(info->port_array[0]) ||
		!loopback_test(info->port_array[1]) ||
		 (info->port_count == 4 && !loopback_test(info->port_array[2])) ||
		 (info->port_count == 4 && !loopback_test(info->port_array[3]))) {
		printk( "%s(%d):DMA test failure for device %s\n",
			__FILE__,__LINE__,info->device_name);
		return -ENODEV;
	}

	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk( "%s(%d):device %s passed diagnostics\n",
			__FILE__,__LINE__,info->device_name );

	info->port_array[0]->init_error = 0;
	info->port_array[1]->init_error = 0;
	if ( info->port_count > 2 ) {
		info->port_array[2]->init_error = 0;
		info->port_array[3]->init_error = 0;
	}

	return 0;
}