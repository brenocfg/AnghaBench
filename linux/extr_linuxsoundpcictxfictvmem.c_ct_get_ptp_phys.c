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
struct ct_vm {TYPE_1__* ptp; } ;
typedef  unsigned long dma_addr_t ;
struct TYPE_2__ {unsigned long addr; } ;

/* Variables and functions */
 int CT_PTP_NUM ; 

__attribute__((used)) static dma_addr_t
ct_get_ptp_phys(struct ct_vm *vm, int index)
{
	return (index >= CT_PTP_NUM) ? ~0UL : vm->ptp[index].addr;
}