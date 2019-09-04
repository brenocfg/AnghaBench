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
struct tty_port {int dummy; } ;
struct fwtty_port {int mstatus; } ;

/* Variables and functions */
 int TIOCM_CAR ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,int) ; 
 struct fwtty_port* port ; 
 struct fwtty_port* to_port (struct tty_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fwtty_port_carrier_raised(struct tty_port *tty_port)
{
	struct fwtty_port *port = to_port(tty_port, port);
	int rc;

	rc = (port->mstatus & TIOCM_CAR);

	fwtty_dbg(port, "%d\n", rc);

	return rc;
}