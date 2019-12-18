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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_debug_disabled () ; 
 int /*<<< orphan*/  err_printk (struct device*,int /*<<< orphan*/ *,char*,void const*,unsigned long) ; 
 scalar_t__ is_vmalloc_addr (void const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_addr_valid (void const*) ; 

void debug_dma_map_single(struct device *dev, const void *addr,
			    unsigned long len)
{
	if (unlikely(dma_debug_disabled()))
		return;

	if (!virt_addr_valid(addr))
		err_printk(dev, NULL, "device driver maps memory from invalid area [addr=%p] [len=%lu]\n",
			   addr, len);

	if (is_vmalloc_addr(addr))
		err_printk(dev, NULL, "device driver maps memory from vmalloc area [addr=%p] [len=%lu]\n",
			   addr, len);
}