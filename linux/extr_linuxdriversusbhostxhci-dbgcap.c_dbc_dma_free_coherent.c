#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xhci_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  sysdev; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,void*,int /*<<< orphan*/ ) ; 
 TYPE_2__* xhci_to_hcd (struct xhci_hcd*) ; 

__attribute__((used)) static inline void
dbc_dma_free_coherent(struct xhci_hcd *xhci, size_t size,
		      void *cpu_addr, dma_addr_t dma_handle)
{
	if (cpu_addr)
		dma_free_coherent(xhci_to_hcd(xhci)->self.sysdev,
				  size, cpu_addr, dma_handle);
}