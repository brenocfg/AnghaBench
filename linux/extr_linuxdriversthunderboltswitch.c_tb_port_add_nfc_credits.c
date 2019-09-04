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
struct TYPE_2__ {scalar_t__ nfc_credits; } ;
struct tb_port {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_PORT ; 
 int /*<<< orphan*/  tb_port_info (struct tb_port*,char*,int,scalar_t__,scalar_t__) ; 
 int tb_port_write (struct tb_port*,scalar_t__*,int /*<<< orphan*/ ,int,int) ; 

int tb_port_add_nfc_credits(struct tb_port *port, int credits)
{
	if (credits == 0)
		return 0;
	tb_port_info(port,
		     "adding %#x NFC credits (%#x -> %#x)",
		     credits,
		     port->config.nfc_credits,
		     port->config.nfc_credits + credits);
	port->config.nfc_credits += credits;
	return tb_port_write(port, &port->config.nfc_credits,
			     TB_CFG_PORT, 4, 1);
}