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
typedef  int /*<<< orphan*/  u64 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,size_t,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_pci_free_coherent(struct device *dev, size_t size,
				  void *cpu_addr, u64 handle)
{
	dma_free_coherent(dev, size, cpu_addr, handle);
}