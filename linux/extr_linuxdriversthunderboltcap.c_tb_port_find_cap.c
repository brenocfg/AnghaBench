#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ type; } ;
struct tb_port {TYPE_1__ config; } ;
struct TYPE_4__ {int cap; int next; } ;
struct tb_cap_any {TYPE_2__ basic; } ;
typedef  enum tb_port_cap { ____Placeholder_tb_port_cap } tb_port_cap ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  TB_CFG_PORT ; 
 scalar_t__ TB_TYPE_DP_HDMI_OUT ; 
 int tb_port_read (struct tb_port*,struct tb_cap_any*,int /*<<< orphan*/ ,int,int) ; 

int tb_port_find_cap(struct tb_port *port, enum tb_port_cap cap)
{
	u32 offset;

	/*
	 * DP out adapters claim to implement TMU capability but in
	 * reality they do not so we hard code the adapter specific
	 * capability offset here.
	 */
	if (port->config.type == TB_TYPE_DP_HDMI_OUT)
		offset = 0x39;
	else
		offset = 0x1;

	do {
		struct tb_cap_any header;
		int ret;

		ret = tb_port_read(port, &header, TB_CFG_PORT, offset, 1);
		if (ret)
			return ret;

		if (header.basic.cap == cap)
			return offset;

		offset = header.basic.next;
	} while (offset);

	return -ENOENT;
}