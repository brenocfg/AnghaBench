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
struct mgsl_struct {int num_tx_holding_buffers; TYPE_1__* tx_holding_buffers; int /*<<< orphan*/  max_frame_size; int /*<<< orphan*/  device_name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int mgsl_alloc_intermediate_txbuffer_memory(struct mgsl_struct *info)
{
	int i;

	if ( debug_level >= DEBUG_LEVEL_INFO )
		printk("%s %s(%d)  allocating %d tx holding buffers\n",
				info->device_name, __FILE__,__LINE__,info->num_tx_holding_buffers);

	memset(info->tx_holding_buffers,0,sizeof(info->tx_holding_buffers));

	for ( i=0; i<info->num_tx_holding_buffers; ++i) {
		info->tx_holding_buffers[i].buffer =
			kmalloc(info->max_frame_size, GFP_KERNEL);
		if (info->tx_holding_buffers[i].buffer == NULL) {
			for (--i; i >= 0; i--) {
				kfree(info->tx_holding_buffers[i].buffer);
				info->tx_holding_buffers[i].buffer = NULL;
			}
			return -ENOMEM;
		}
	}

	return 0;

}