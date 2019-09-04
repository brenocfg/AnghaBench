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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SPXX_INT_MSK (int) ; 
 int /*<<< orphan*/  CVMX_STXX_INT_MSK (int) ; 
 int /*<<< orphan*/  OCTEON_IRQ_RML ; 
 int /*<<< orphan*/  cvm_oct_common_uninit (struct net_device*) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ number_spi_ports ; 

void cvm_oct_spi_uninit(struct net_device *dev)
{
	int interface;

	cvm_oct_common_uninit(dev);
	number_spi_ports--;
	if (number_spi_ports == 0) {
		for (interface = 0; interface < 2; interface++) {
			cvmx_write_csr(CVMX_SPXX_INT_MSK(interface), 0);
			cvmx_write_csr(CVMX_STXX_INT_MSK(interface), 0);
		}
		free_irq(OCTEON_IRQ_RML, &number_spi_ports);
	}
}