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
typedef  int u16 ;
struct MPT3SAS_ADAPTER {TYPE_1__* pcie_sg_lookup; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  pcie_sgl_dma; } ;

/* Variables and functions */

dma_addr_t
mpt3sas_base_get_pcie_sgl_dma(struct MPT3SAS_ADAPTER *ioc, u16 smid)
{
	return ioc->pcie_sg_lookup[smid - 1].pcie_sgl_dma;
}