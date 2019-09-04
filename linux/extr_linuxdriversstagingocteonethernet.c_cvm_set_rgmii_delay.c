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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ASXX_RX_CLK_SETX (int,int) ; 
 int /*<<< orphan*/  CVMX_ASXX_TX_CLK_SETX (int,int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cvm_set_rgmii_delay(struct device_node *np, int iface, int port)
{
	u32 delay_value;

	if (!of_property_read_u32(np, "rx-delay", &delay_value))
		cvmx_write_csr(CVMX_ASXX_RX_CLK_SETX(port, iface), delay_value);
	if (!of_property_read_u32(np, "tx-delay", &delay_value))
		cvmx_write_csr(CVMX_ASXX_TX_CLK_SETX(port, iface), delay_value);
}