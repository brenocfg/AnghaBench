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
struct tty_struct {int dummy; } ;
struct TYPE_2__ {int RTS; } ;
struct port {int update_flow_control; TYPE_1__ ctrl_ul; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_CTRL ; 
 int /*<<< orphan*/  enable_transmit_ul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dc_by_tty (struct tty_struct const*) ; 
 struct port* get_port_by_tty (struct tty_struct const*) ; 

__attribute__((used)) static void set_rts(const struct tty_struct *tty, int rts)
{
	struct port *port = get_port_by_tty(tty);

	port->ctrl_ul.RTS = rts;
	port->update_flow_control = 1;
	enable_transmit_ul(PORT_CTRL, get_dc_by_tty(tty));
}