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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rio_mport {int dummy; } ;

/* Variables and functions */

int rio_enable_rx_tx_port(struct rio_mport *port,
			  int local, u16 destid,
			  u8 hopcount, u8 port_num)
{
#ifdef CONFIG_RAPIDIO_ENABLE_RX_TX_PORTS
	u32 regval;
	u32 ext_ftr_ptr;
	u32 rmap;

	/*
	* enable rx input tx output port
	*/
	pr_debug("rio_enable_rx_tx_port(local = %d, destid = %d, hopcount = "
		 "%d, port_num = %d)\n", local, destid, hopcount, port_num);

	ext_ftr_ptr = rio_mport_get_physefb(port, local, destid,
					    hopcount, &rmap);

	if (local) {
		rio_local_read_config_32(port,
				ext_ftr_ptr + RIO_PORT_N_CTL_CSR(0, rmap),
				&regval);
	} else {
		if (rio_mport_read_config_32(port, destid, hopcount,
			ext_ftr_ptr + RIO_PORT_N_CTL_CSR(port_num, rmap),
				&regval) < 0)
			return -EIO;
	}

	regval = regval | RIO_PORT_N_CTL_EN_RX | RIO_PORT_N_CTL_EN_TX;

	if (local) {
		rio_local_write_config_32(port,
			ext_ftr_ptr + RIO_PORT_N_CTL_CSR(0, rmap), regval);
	} else {
		if (rio_mport_write_config_32(port, destid, hopcount,
			ext_ftr_ptr + RIO_PORT_N_CTL_CSR(port_num, rmap),
				regval) < 0)
			return -EIO;
	}
#endif
	return 0;
}