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
struct il_priv {TYPE_1__* pci_dev; } ;
struct il_dma_ptr {size_t size; int /*<<< orphan*/  addr; int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
il4965_alloc_dma_ptr(struct il_priv *il, struct il_dma_ptr *ptr, size_t size)
{
	ptr->addr = dma_alloc_coherent(&il->pci_dev->dev, size, &ptr->dma,
				       GFP_KERNEL);
	if (!ptr->addr)
		return -ENOMEM;
	ptr->size = size;
	return 0;
}