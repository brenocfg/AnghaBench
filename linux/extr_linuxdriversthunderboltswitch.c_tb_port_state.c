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
struct tb_port {scalar_t__ cap_phy; } ;
struct tb_cap_phy {int state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TB_CFG_PORT ; 
 int /*<<< orphan*/  tb_port_WARN (struct tb_port*,char*) ; 
 int tb_port_read (struct tb_port*,struct tb_cap_phy*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int tb_port_state(struct tb_port *port)
{
	struct tb_cap_phy phy;
	int res;
	if (port->cap_phy == 0) {
		tb_port_WARN(port, "does not have a PHY\n");
		return -EINVAL;
	}
	res = tb_port_read(port, &phy, TB_CFG_PORT, port->cap_phy, 2);
	if (res)
		return res;
	return phy.state;
}