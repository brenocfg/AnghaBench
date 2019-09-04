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
struct TYPE_2__ {void (* dma_callback ) (void*) ;void* dma_callback_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 TYPE_1__ lcdc ; 

int omap_lcdc_set_dma_callback(void (*callback)(void *data), void *data)
{
	BUG_ON(callback == NULL);

	if (lcdc.dma_callback)
		return -EBUSY;
	else {
		lcdc.dma_callback = callback;
		lcdc.dma_callback_data = data;
	}
	return 0;
}