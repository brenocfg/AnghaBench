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
struct cas_tx_desc {void* buffer; void* control; } ;
struct cas {struct cas_tx_desc** init_txds; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_BASE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TX_DESC_BUFLEN ; 
 int /*<<< orphan*/  TX_DESC_EOF ; 
 int /*<<< orphan*/  TX_DESC_INTME ; 
 scalar_t__ cas_intme (int,int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cas_write_txd(struct cas *cp, int ring, int entry,
			  dma_addr_t mapping, int len, u64 ctrl, int last)
{
	struct cas_tx_desc *txd = cp->init_txds[ring] + entry;

	ctrl |= CAS_BASE(TX_DESC_BUFLEN, len);
	if (cas_intme(ring, entry))
		ctrl |= TX_DESC_INTME;
	if (last)
		ctrl |= TX_DESC_EOF;
	txd->control = cpu_to_le64(ctrl);
	txd->buffer = cpu_to_le64(mapping);
}