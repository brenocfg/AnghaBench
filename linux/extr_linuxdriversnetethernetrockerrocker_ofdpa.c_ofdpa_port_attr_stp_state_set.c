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
struct rocker_port {struct ofdpa_port* wpriv; } ;
struct ofdpa_port {int dummy; } ;

/* Variables and functions */
 int ofdpa_port_stp_update (struct ofdpa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ofdpa_port_attr_stp_state_set(struct rocker_port *rocker_port,
					 u8 state)
{
	struct ofdpa_port *ofdpa_port = rocker_port->wpriv;

	return ofdpa_port_stp_update(ofdpa_port, 0, state);
}