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
struct rocker_port {struct ofdpa_port* wpriv; } ;
struct ofdpa_port {int dummy; } ;
struct ofdpa {TYPE_1__* rocker; } ;
struct TYPE_2__ {struct rocker_port** ports; } ;

/* Variables and functions */

__attribute__((used)) static struct ofdpa_port *ofdpa_port_get(const struct ofdpa *ofdpa,
					 int port_index)
{
	struct rocker_port *rocker_port;

	rocker_port = ofdpa->rocker->ports[port_index];
	return rocker_port ? rocker_port->wpriv : NULL;
}