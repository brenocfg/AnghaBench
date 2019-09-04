#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  napi; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  CVMX_POW_WQ_INT_THRX (int) ; 
 int /*<<< orphan*/  CVMX_SSO_WQ_INT_THRX (int) ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvm_oct_device ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 TYPE_1__* oct_rx_group ; 
 int pow_receive_groups ; 

void cvm_oct_rx_shutdown(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(oct_rx_group); i++) {
		if (!(pow_receive_groups & BIT(i)))
			continue;

		/* Disable POW interrupt */
		if (OCTEON_IS_MODEL(OCTEON_CN68XX))
			cvmx_write_csr(CVMX_SSO_WQ_INT_THRX(i), 0);
		else
			cvmx_write_csr(CVMX_POW_WQ_INT_THRX(i), 0);

		/* Free the interrupt handler */
		free_irq(oct_rx_group[i].irq, cvm_oct_device);

		netif_napi_del(&oct_rx_group[i].napi);
	}
}