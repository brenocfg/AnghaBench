#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cas {int* rx_old; int cas_flags; scalar_t__ regs; TYPE_1__** init_rxds; } ;
struct TYPE_5__ {int dma_addr; } ;
typedef  TYPE_2__ cas_page_t ;
struct TYPE_4__ {void* index; void* buffer; } ;

/* Variables and functions */
 int CAS_BASE (int /*<<< orphan*/ ,int const) ; 
 int CAS_FLAG_REG_PLUS ; 
 int N_RX_DESC_RINGS ; 
 scalar_t__ REG_PLUS_RX_KICK1 ; 
 scalar_t__ REG_RX_KICK ; 
 int RX_DESC_ENTRY (int const,int) ; 
 int /*<<< orphan*/  RX_INDEX_NUM ; 
 int /*<<< orphan*/  RX_INDEX_RING ; 
 TYPE_2__* cas_page_swap (struct cas*,int const,int const) ; 
 void* cpu_to_le64 (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cas_post_page(struct cas *cp, const int ring, const int index)
{
	cas_page_t *new;
	int entry;

	entry = cp->rx_old[ring];

	new = cas_page_swap(cp, ring, index);
	cp->init_rxds[ring][entry].buffer = cpu_to_le64(new->dma_addr);
	cp->init_rxds[ring][entry].index  =
		cpu_to_le64(CAS_BASE(RX_INDEX_NUM, index) |
			    CAS_BASE(RX_INDEX_RING, ring));

	entry = RX_DESC_ENTRY(ring, entry + 1);
	cp->rx_old[ring] = entry;

	if (entry % 4)
		return;

	if (ring == 0)
		writel(entry, cp->regs + REG_RX_KICK);
	else if ((N_RX_DESC_RINGS > 1) &&
		 (cp->cas_flags & CAS_FLAG_REG_PLUS))
		writel(entry, cp->regs + REG_PLUS_RX_KICK1);
}