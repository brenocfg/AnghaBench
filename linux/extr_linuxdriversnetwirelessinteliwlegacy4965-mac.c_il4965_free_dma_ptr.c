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
struct il_dma_ptr {int /*<<< orphan*/  dma; int /*<<< orphan*/  addr; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct il_dma_ptr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void
il4965_free_dma_ptr(struct il_priv *il, struct il_dma_ptr *ptr)
{
	if (unlikely(!ptr->addr))
		return;

	dma_free_coherent(&il->pci_dev->dev, ptr->size, ptr->addr, ptr->dma);
	memset(ptr, 0, sizeof(*ptr));
}