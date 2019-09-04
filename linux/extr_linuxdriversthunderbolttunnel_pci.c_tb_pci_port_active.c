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
typedef  int u32 ;
struct tb_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_PORT ; 
 int /*<<< orphan*/  TB_PORT_CAP_ADAP ; 
 int tb_port_find_cap (struct tb_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_port_warn (struct tb_port*,char*,int) ; 
 int tb_port_write (struct tb_port*,int*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tb_pci_port_active(struct tb_port *port, bool active)
{
	u32 word = active ? 0x80000000 : 0x0;
	int cap = tb_port_find_cap(port, TB_PORT_CAP_ADAP);
	if (cap < 0) {
		tb_port_warn(port, "TB_PORT_CAP_ADAP not found: %d\n", cap);
		return cap;
	}
	return tb_port_write(port, &word, TB_CFG_PORT, cap, 1);
}